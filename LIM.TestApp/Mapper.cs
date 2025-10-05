using log4net;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace LIM
{
    public class Mapper
    {
        private static readonly ILog Logger = LogManager.GetLogger(System.Reflection.MethodBase.GetCurrentMethod().DeclaringType);
        public static string[] DefSeperators_0 = new String[] { " ", ",", ".", "(", ")", "\"" };
        public static string[] XmlSeperators_1 = new String[] { " ", ",", ".", "(", ")", "<", "/>", "=" };
        public static string[] AllSeperators_2 = new String[] { " ", ",", ".", "(", ")", "<", "/>", "=", "[", "]", "{", "}", "$", "#", "@", "!", "%", "^", "&", "*", "_", "-", "+", ":", "'" };
        private static string[] _chosenSeperator;
        private static string[][] _allSeperators = new string[][] { DefSeperators_0, XmlSeperators_1, AllSeperators_2 };
        private Dictionary<string, string> _upperCaseReplacementDictionary = new Dictionary<string, string>();
        public Dictionary<string, string> _replacementDic = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase);
        public Dictionary<string, string> _inverseDic = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase);
        private ConcurrentDictionary<string, int> _allWords = new System.Collections.Concurrent.ConcurrentDictionary<string, int>(StringComparer.OrdinalIgnoreCase);
        private ConcurrentQueue<LogMessage> _messagesToParse = new ConcurrentQueue<LogMessage>();
        private ConcurrentQueue<LogMessage> _parsedMessages = new ConcurrentQueue<LogMessage>();
        private string _inputFile, _outputFile, _mapFile, _inputFileNew;
        private string _outputFir;
        private MessageFilter _filter;

        public Mapper(string fileName, string outputDir, string[] seperatorArray, MessageFilter filter, string specialChar = "~")
        {
            _chosenSeperator = seperatorArray;
            _filter = filter;                                                            
            _specialChar = specialChar;
            PrepOutput(fileName, outputDir);
        }

        private void PrepOutput(string sourceFile, string destFolder)
        {            
            _outputFir = destFolder;
            _inputFile = sourceFile;
            var original = Path.Combine(_outputFir, Path.GetFileNameWithoutExtension(sourceFile)) + "_org.log";
            _outputFile = Path.Combine(_outputFir, Path.GetFileNameWithoutExtension(sourceFile)) + "_short.log";
            _mapFile = Path.Combine(_outputFir, Path.GetFileNameWithoutExtension(sourceFile)) + "_map.log";
            _inputFileNew = Path.Combine(_outputFir, Path.GetFileNameWithoutExtension(sourceFile)) + "_new.log";

            if(File.Exists(original))
            {
                File.Delete(original);
            }
            if (File.Exists(_outputFile))
            {
                File.Delete(_outputFile);
            }
            if (File.Exists(_mapFile))
            {
                File.Delete(_mapFile);
            }
            if (File.Exists(_inputFileNew))
            {
                File.Delete(_inputFileNew);
            }
            File.Copy(sourceFile, original);
        }

        public MappingResult Map()
        {
            SetFreeStrings();
            var res =  ReadAllLines(_inputFile);
            CreateMapping();
            WriteAllLines(_outputFile,  res);
            RewriteFile(_outputFile, _inputFileNew);
            return res;
        }
        
        private string _specialChar = "~";
        private bool fileDone = false, started = false;

        private List<string> _freeStrings = new List<string>();

        private void SetFreeStrings()
        {
            Logger.Debug("Starting SetFreeStrings");
            DateTime start = DateTime.Now;


            for (var i = 'a'; i < 'z'; ++i)
            {
                _freeStrings.Add(_specialChar + i.ToString());
            }

            for (var i = '0'; i < '9'; ++i)
            {
                _freeStrings.Add(_specialChar + i.ToString());
            }

            for (var i = 'a'; i < 'z'; ++i)
            {
                for (var j = 'a'; j < 'z'; ++j)
                {
                    _freeStrings.Add(_specialChar + i.ToString() + j.ToString());
                }
                for (var j = '0'; j < '9'; ++j)
                {
                    _freeStrings.Add(_specialChar + i.ToString() + j.ToString());
                }
            }

            for (var i = '0'; i < '9'; ++i)
            {
                for (var j = 'a'; j < 'z'; ++j)
                {
                    _freeStrings.Add(_specialChar + i.ToString() + j.ToString());
                }
                for (var j = '0'; j < '9'; ++j)
                {
                    _freeStrings.Add(_specialChar + i.ToString() + j.ToString());
                }
            }

            for (var i = 'a'; i < 'z'; ++i)
            {
                for (var j = 'a'; j < 'z'; ++j)
                {
                    for (var k = 'a'; k < 'z'; ++k)
                    {
                        _freeStrings.Add(_specialChar + i.ToString() + j.ToString() + k.ToString());
                    }
                }
            }

            var span = DateTime.Now - start;
            Logger.Debug(string.Format("Finished SetFreeStrings for {0} keys within {1} seconds", _freeStrings.Count, span.TotalSeconds));
        }

        private MappingResult ReadAllLines(string fileName)
        {
            var mapRes = new MappingResult();
            Logger.DebugFormat("Starting ReadAllLines {0}", fileName);
            var fi = new FileInfo(fileName);
            mapRes.FileSizeInKb = fi.Length / 1024;

            DateTime start = DateTime.Now;
            System.IO.StreamReader file = new System.IO.StreamReader(fileName);

            
            ReadMessages(file);
            file.Close();
            fileDone = true;
            mapRes.MessageCount = _messagesToParse.Count;
       
            var res = Task.Factory.StartNew(() =>
            {
                StartDequeuinMessages();
            });

            while (!res.IsCompleted)
            {
                System.Threading.Thread.Sleep(5000);
            }            

            var span = DateTime.Now - start;
            Logger.Debug(string.Format("Finished ReadAllLines within {0} seconds", span.TotalSeconds));
            return mapRes;
        }

        private string GetFreeStr()
        {
            if (_freeStrings.Count == 0)
            {
                return string.Empty;
            }
            return _freeStrings[0];
        }

        private void RemoveStr()
        {
            _freeStrings.RemoveAt(0);
        }

        private void CreateMapping()
        {
            // only work with strings which appear at least 10 times
            var counts = _allWords.Where(w=>w.Value>10).OrderByDescending(k => (k.Key.Length) * k.Value);
            foreach (var c in counts)
            {
                try
                {
                    Logger.Debug(string.Format("{0} {1} {2}", c.Key, c.Value, c.Key.Length * c.Value));
                    var shortStr = GetFreeStr();
                    if (c.Key.Length <= shortStr.Length)
                    {
                        continue;
                    }
                    if (shortStr == string.Empty)
                    {
                        return;
                    }
                    RemoveStr();
                    var strToReplace = c.Key;
                    var upperCaseStrToReplace = strToReplace.ToUpper();
                    //Regex.Escape(c.Key);
                    if (_replacementDic.ContainsKey(upperCaseStrToReplace) || _inverseDic.ContainsKey(shortStr))
                    {
                        Logger.DebugFormat("{0}=>{1} exists", strToReplace, shortStr);
                    }

                    _upperCaseReplacementDictionary.Add(upperCaseStrToReplace, strToReplace);
                    _replacementDic.Add(upperCaseStrToReplace, shortStr);
                    _inverseDic.Add(shortStr, strToReplace);
                    Logger.DebugFormat("{0}=>{1}", strToReplace, shortStr);
                }
                catch (Exception ex)
                {
                    Logger.Error(ex);
                }
            }
            PrintDictionaryToFs(_mapFile);
            //Console.ReadKey();
        }

        private void PrintDictionaryToFs(string fileName)
        {
            if (_replacementDic == null || _replacementDic.Keys.Count == 0)
            {
                return;
            }
            File.Create(fileName).Close();
            var sb = new StringBuilder();

            foreach (var k in _replacementDic.Keys)
            {
                var upperCaseKey = k;
                var shortStr = _replacementDic[k];
                var originalStr = _upperCaseReplacementDictionary[upperCaseKey];
                sb.AppendLine(string.Format("{0},{1}", shortStr, originalStr));
            }
            File.WriteAllText(fileName, sb.ToString());
        }

        private void StartDequeuinMessages()
        {
            LogMessage message;
            Logger.Debug("Starting to wait for messages");
            while (!started)
            {
                Thread.Sleep(1000);
            }
            Logger.Debug("Starting StartDequeuinMessages");
            var start = DateTime.Now;
            var taskList = new List<Task>();
            var source = new CancellationTokenSource();
            var token = source.Token;
            var gotMessage = true;
            while (true)
            {
                gotMessage = _messagesToParse.TryDequeue(out message);

                if (gotMessage == true && message != null)
                {
                    var me = message;                    
                    _parsedMessages.Enqueue(me);
                    taskList.Add(Task.Run(new Action(()=>
                    { AnalyzeMessage(me); }), token));
                }
                if (_messagesToParse.Count == 0)
                {
                    Thread.Sleep(2000);
                    var done = Task.WaitAll(taskList.ToArray(), 3600 * 1000);
                    if (_messagesToParse.Count == 0)
                    {
                        Logger.DebugFormat("No more message to parse... parsing completed = {0}", done);
                        break;
                    }
                }
            }

            var span = DateTime.Now - start;
            Logger.Debug(string.Format("Finished StartDequeuinMessages within {0} seconds", span.TotalSeconds));
        }

        private bool FilterLine(string input, out string output, out string prefix)
        {
            output = input;
            prefix = string.Empty;
            var res = false;

            if(_filter.TableFilter!=null)
            {
                var newOutput = string.Empty;
                var allcolumns = input.Split(_filter.TableFilter.Seperators.ToArray(), StringSplitOptions.RemoveEmptyEntries).ToList();
                for(var i=0;i<allcolumns.Count();++i)
                {
                    if(_filter.TableFilter.ColumnsToIgnore.Contains(i))
                    {
                        if (prefix == string.Empty)
                        {
                            prefix = string.Format("{0}", allcolumns[i]);
                        }
                        else
                        {
                            prefix = string.Format("{0}{1}{2}", prefix, _filter.TableFilter.Seperators.First(), allcolumns[i]);
                        }
                    }
                    else
                    {
                        newOutput = string.Format("{0}{1}{2}", newOutput, _filter.TableFilter.Seperators.First(), allcolumns[i]);
                    }
                }
                output = newOutput;
                return true;
            }

            if (!string.IsNullOrEmpty(_filter.IgnoreFrom) && !string.IsNullOrEmpty(_filter.IgnoreTo))
            {
                var splt = input.Split(new string[] { _filter.IgnoreFrom, _filter.IgnoreTo }, StringSplitOptions.RemoveEmptyEntries);
                // get the last string following the date-time
                output = splt.LastOrDefault();
                var indx = input.IndexOf(output);
                // get the const string including date-time to attach to first message line
                prefix = input.Substring(0, indx);
                //return true;
            }
            if(_filter.IgnoreStart>0)
            {
                prefix = output.Substring(0, _filter.IgnoreStart);
                output = output.Substring(_filter.IgnoreStart);
                //res = true;
            }
            if (!string.IsNullOrEmpty(_filter.DtFormat))
            {
                DateTime dt;
                string str;
                var foundDt = Helper.GetDateTimeFromString(output, out dt, out str);
                if (foundDt == true)
                {
                    prefix += output.Substring(0, _filter.DtFormat.Length);
                    output = output.Substring(_filter.DtFormat.Length);
                    res = true; 
                }                          
            }
            if (_filter.IgnoreEnd > 0)
            {
                prefix += output.Substring(0, _filter.IgnoreEnd);
                output = output.Substring(_filter.IgnoreEnd);
                //res = true;
            }
            return res;
        }

        private void AnalyzeMessage(LogMessage message)
        {
            try
            {
                if (message == null || message.Lines == null)
                {
                    return;
                }

                Logger.DebugFormat("Starting to analyze {0}", message.ToString());
                if (!message.Lines.Any())
                {
                    return;
                }
                var size = 0;
                foreach (var l in message.Lines)
                {
                    size += l.WholeLine.Length;
                    var split = l.Text.Split(_chosenSeperator, StringSplitOptions.RemoveEmptyEntries);
                    //DateTime dt;
                    //var hasDateTime = Helper.GetDateTimeFromString(l, out dt);

                    //split = split.Skip(3).ToArray();
                    foreach (var word in split)
                    {
                        //Logger.DebugFormat("Updating {0}", word);
                        _allWords.AddOrUpdate(word, 1, (w, n) => { return n + 1; });
                    }
                }
                message.LimRes.OriginalMessageSize = size;
            }
            catch(Exception ex)
            {
                Logger.WarnFormat("Exception {0} for message {1}", ex, message.ToString());
                    
            }
        }

        private void CreateShrunkFile(StreamWriter newFile, MappingResult mappingRes)
        {
            Logger.Debug("Starting CreateShrunkFile");
            var messageCount = _parsedMessages.Count;
            DateTime start = DateTime.Now;
            var res = Parallel.ForEach(_parsedMessages, ShortenMessage);

            while (res.IsCompleted == false)
            {
                Thread.Sleep(5000);
            }
            var span = DateTime.Now - start;
            mappingRes.AvgLimMessageSize = _parsedMessages.Average(m => m.LimRes.LimMessageSize);
            mappingRes.AvgMessageSize = _parsedMessages.Average(m => m.LimRes.OriginalMessageSize);

            start = DateTime.Now;
            Logger.Debug(string.Format("Finished Shrinking {0} messages within {1} seconds", messageCount, span.TotalSeconds));
            foreach (var m in _parsedMessages)
            {
                foreach (var l in m.Lines)
                {
                    if (_filter.TableFilter != null)
                    {
                        newFile.WriteLine(l.Prefix + this._filter.TableFilter.Seperators.First() + l.Text);
                    }
                    else
                    {
                        newFile.WriteLine(l.WholeLine);
                    }
                }
            }
            span = DateTime.Now - start;
            Logger.Debug(string.Format("Finished CreateShrunkFile within {0} seconds", span.TotalSeconds));
        }

        private void ShortenMessage(LogMessage message)
        {
            var res = new LimRes();

            try
            {
                var newLines = new List<LogLine>();
                var count = message.Lines.Count();
                var size = 0;                
                var start = DateTime.Now;
                bool isFirstLine = true, parsed = false;
                string fl, prefix = string.Empty;

                for (var i = 0; i < count; ++i)
                {
                    var line = new LogLine();
                    // remove the shishito character if exists
                    var l = message.Lines[0].Text.Replace(_specialChar, string.Empty);

                    if (isFirstLine == true)
                    {
                        // get the line with seperated prefix                      
                        parsed = FilterLine(l, out fl, out prefix);// Helper.GetDateTimeFromString(l, out dt);
                        if (parsed == true)
                        {
                            l = fl;
                        }                        
                    }

                    // switch to uppercase
                    string nl = l.ToUpper();

                    // remove old line
                    message.Lines.RemoveAt(0);

                    // replace all original strings using dic
                    foreach (var k in _replacementDic.Keys.OrderByDescending(k => k.Length))
                    {
                        nl = nl.Replace(k, _replacementDic[k]);
                    }
                    
                    line.Text = nl;

                    // reattahc the prefix
                    if (isFirstLine==true && parsed == true) //re attach the prefix string (date time)
                    {                       
                        line.Prefix = prefix;                        
                        isFirstLine = false;
                    }
                    size += nl.Length;
                    newLines.Add(line);
                }
                message.Lines = newLines;
                var end = DateTime.Now;
                res.LimDuration = end - start;
                res.LimMessageSize = size;
                res.OriginalMessageSize = message.LimRes.OriginalMessageSize;
                // Logger.Debug("Finished" + message.DateTime.ToString("yyyy-MM-dd HH:mm:ss,fff"));
            }
            catch (Exception ex)
            {
                Logger.Debug(ex);
            }
            message.LimRes = res;
        }

        private void ReadMessages(StreamReader file)
        {
            string line;
            var message = new List<string>();
            LogMessage currentMessage = null;
            var rows = 0;

            while ((line = file.ReadLine()) != null)
            {
                rows++;
                try
                {
                    Logger.DebugFormat("Parsing {0}", line);
                    var parsed = line.Split(new string[] { " ", ",", "." }, StringSplitOptions.RemoveEmptyEntries);
                    if (!parsed.Any())
                    {
                        continue;
                    }

                    DateTime dt = DateTime.MinValue;
                    string newStr, prefix;
                    //var res = Helper.GetDateTimeFromString(line, out dt, out newStr);
                     var res=FilterLine(line, out newStr, out prefix);
                     var logLine = new LogLine { Text = newStr, Prefix = prefix };
                    if (res == true)
                    {
                        if (currentMessage != null)
                        {
                            _messagesToParse.Enqueue(currentMessage);
                        }
                        currentMessage = new LogMessage { DateTime = dt };

                        currentMessage.Lines = new List<LogLine> { logLine };
                        started = true;
                    }
                    else
                    {
                        if (currentMessage != null)
                        {
                            currentMessage.Lines.Add(logLine);
                        }
                    }
                }
                catch (Exception ex)
                {
                    Logger.Error(ex);
                }

            }
            if (currentMessage != null)
            {
                Logger.DebugFormat("Enqueuing {0}", currentMessage.Lines.Any()? currentMessage.Lines.First().Text:"empty");
                _messagesToParse.Enqueue(currentMessage);
            }
            //var stopped = 0;
        }

        private void RewriteFile(string filename, string newFileName)
        {
            Logger.Debug("Starting RewriteFile");
            DateTime start = DateTime.Now;
            System.IO.StreamReader file = new System.IO.StreamReader(filename);
            System.IO.StreamWriter newFile = new StreamWriter(newFileName);
            string line;
            while ((line = file.ReadLine()) != null)
            {
                foreach (var k in _inverseDic.Keys.Reverse())
                {
                    //var regex = new 
                    //line = Regex.Replace(line, k, Regex.Escape(_inveseDic[k]), RegexOptions.IgnoreCase);
                    line = line.Replace(k, _inverseDic[k]);
                }
                newFile.WriteLine(line);
            }

            newFile.Close();
            file.Close();

            var span = DateTime.Now - start;
            Logger.Debug(string.Format("Finished RewriteFile within {0} seconds", span.TotalSeconds));

        }

        private void WriteAllLines(string fileName, MappingResult mappingRes)
        {
            StreamWriter file = new StreamWriter(fileName);
            CreateShrunkFile(file, mappingRes);
            file.Close();
        }

    }
}
