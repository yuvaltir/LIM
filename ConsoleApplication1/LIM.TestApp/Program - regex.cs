using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
//using LIM;
using log4net;
using System.Reflection;
using System.Text.RegularExpressions;
[assembly: log4net.Config.XmlConfigurator(Watch = true)]

namespace ConsoleApplication1
{
    class Program
    {
        private static string _specialChar = "~";
        private static bool fileDone = false, started = false;
        private class Message
        {
            DateTime _dateTime;

            public DateTime DateTime
            {
                get { return _dateTime; }
                set { _dateTime = value; }
            }

            List<string> _lines;

            public List<string> Lines
            {
              get { return _lines; }
              set { _lines = value; }
            }
        }
        //private static readonly ILog Logger = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);

        private static List<string> _freeStrings = new List<string>();
        private static string _dicFile = @"C:\Users\yt250091\Downloads\R10\map.log";

        static void Main(string[] args)
        {
//            var t = new LIM.LimAppender().GetType();
            
            //Logger.DebugFormat("Testing,1,2,3 {0}", "arg1");
            var resFile = @"C:\Users\yt250091\Downloads\R10\ServeRes.log";
            var reverseFile = @"C:\Users\yt250091\Downloads\R10\ReverseRes.log";
            
            SetFreeStrings();
            ReadAllLines(args[0]);
            WriteAllLines(resFile);           
            RewriteFile(resFile, reverseFile);
        }

        private static void WriteAllLines(string fileName)
        {
            StreamWriter file = new StreamWriter(fileName);
            CreateShrunkFile(file);
            file.Close();
        }

        static void SetFreeStrings()
        {
            Console.WriteLine("Starting SetFreeStrings");
            DateTime start = DateTime.Now;


            for(var i='a';i<'z';++i)
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
            Console.WriteLine(string.Format("Finished SetFreeStrings for {0} keys within {1} seconds",_freeStrings.Count,span.TotalSeconds));
        }

        static Dictionary<string, string> _replacementDic = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase);

        static Dictionary<string, string> _inveseDic = new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase);

        static ConcurrentDictionary<string, int> _allWords = new System.Collections.Concurrent.ConcurrentDictionary<string, int>(StringComparer.OrdinalIgnoreCase);

        static ConcurrentQueue<Message> _messagesToParse = new ConcurrentQueue<Message>();

        static ConcurrentQueue<Message> _parsedMessages = new ConcurrentQueue<Message>();

        private static void ReadAllLines(string filename)
        {
            Console.WriteLine("Starting ReadAllLines");
            DateTime start = DateTime.Now;
            System.IO.StreamReader file =   new System.IO.StreamReader(filename);

            //Task.Factory.StartNew(() =>
            //{
                ReadMessage(file);
                file.Close();
                fileDone = true;
            //});
            var res = Task.Factory.StartNew(() =>
            {
                StartDequeuinMessages();
            });
                
                while(!res.IsCompleted)
                {
                    System.Threading.Thread.Sleep(5000);
                }
                PrintResults();


                var span = DateTime.Now - start;
                Console.WriteLine(string.Format("Finished ReadAllLines within {0} seconds", span.TotalSeconds));
        }

        private static string GetFreeStr() 
        {
            if(_freeStrings.Count==0)
            {
                return string.Empty;
            }
            return _freeStrings[0];                        
        }

        private static void RemoveStr()
        {
            _freeStrings.RemoveAt(0);
        }

        private static void PrintResults()
        {
            var counts = _allWords.OrderByDescending(k =>  (k.Key.Length) * k.Value );
            foreach(var c in counts)
            {
                try
                {
                   
                    //Console.WriteLine(string.Format("{0} {1} {2}", c.Key, c.Value, c.Key.Length * c.Value));
                    var shortStr = GetFreeStr();
                    if (c.Key.Length <= shortStr.Length)
                    {
                        continue;
                    }
                    if(shortStr==string.Empty)
                    {
                        return;
                    }
                    RemoveStr();
                    if (_replacementDic.ContainsKey(c.Key) || _inveseDic.ContainsKey(shortStr))
                    {
                        Console.WriteLine("{0}=>{1} exists", c.Key, shortStr);
                    }

                    _replacementDic.Add(c.Key, shortStr);
                    _inveseDic.Add(shortStr, c.Key);
                    Console.WriteLine("{0}=>{1}",c.Key,shortStr);
                }
                catch(Exception ex)
                {
                    Console.WriteLine(ex);
                }
            }
            PrintDictionaryToFs();
            Console.ReadKey();
        }

        private static void PrintDictionaryToFs()
        {
            if(_replacementDic==null || _replacementDic.Keys.Count==0)
            {
                return;
            }
            File.Create(_dicFile).Close();
            var sb = new StringBuilder();
            
            foreach(var k in _replacementDic .Keys)
            {                
                sb.AppendLine(string.Format("{0},{1}",k,_replacementDic[k]));
            }
            File.WriteAllText(_dicFile,sb.ToString());
        }

        private static void StartDequeuinMessages()
        {
            Message message;
            while (!started) 
            {

            }
            Console.WriteLine("Starting StartDequeuinMessages");
            DateTime start = DateTime.Now;
            var gotMessage = true;
            while (true)
            {
                gotMessage = _messagesToParse.TryDequeue(out message);
                
                if (gotMessage==true && message != null)
                {
                    var me = message;
                    _parsedMessages.Enqueue(me);
                    Task.Factory.StartNew(()=>
                    AnalyzeMessage(me));
                }
                if(_messagesToParse.Count==0)
                {
                    Thread.Sleep(2000);
                    if (_messagesToParse.Count == 0)
                    {
                        break;
                    }
                }                
            }

            var span = DateTime.Now - start;
            Console.WriteLine(string.Format("Finished StartDequeuinMessages within {0} seconds", span.TotalSeconds));
        }

        private static void AnalyzeMessage(Message message)
        {

            if (message == null)
                return;
                if(!message.Lines.Any())
            {
                return;
            }
            foreach(var l in message.Lines)
            {
                var split = l.Split(new String[] { " ",",",".","(",")" }, StringSplitOptions.RemoveEmptyEntries);
                DateTime dt;
                var hasDateTime = GetDateTimeFromString(l, out dt);

                split = split.Skip(3).ToArray();
                foreach(var word in split)
                {                    
                    _allWords.AddOrUpdate(word,1,(w,n)=>{ return n+1; });
                }
            }
        }

        private static void CreateShrunkFile(StreamWriter newFile )
        {
            Console.WriteLine("Starting CreateShrunkFile");
            var messageCount = _parsedMessages.Count;
            DateTime start = DateTime.Now;
            var res = Parallel.ForEach(_parsedMessages, ShortenMessage);
            
            while(res.IsCompleted==false)
            {
                Thread.Sleep(5000);
            }
            var span = DateTime.Now - start;
            start = DateTime.Now;
            Console.WriteLine(string.Format("Finished Shrinking {0} messages within {1} seconds",messageCount, span.TotalSeconds));
            foreach(var m in _parsedMessages)
            {
                foreach(var l in m.Lines)
                {
                    newFile.WriteLine(l);
                }
            }
            span = DateTime.Now - start;
            Console.WriteLine(string.Format("Finished CreateShrunkFile within {0} seconds", span.TotalSeconds));                                   
        }

        private static void ShortenMessage(Message message)
        {
            try
            {
                var newLines = new List<string>();
                var count = message.Lines.Count();
                
                for (var i = 0; i < count; ++i)
                {
                    var l = message.Lines[0].Replace(_specialChar,string.Empty);                 

                    DateTime dt;
                    var parsed = GetDateTimeFromString(l, out dt);
                    if(parsed==true)
                    {
                        l = l.Remove(0, 24);
                    }

                    string nl = l.ToUpper();

                    message.Lines.RemoveAt(0);
                    foreach (var k in _replacementDic.Keys)
                    {
                        try
                        {
                            nl = Regex.Replace(nl, Regex.Escape(k), _replacementDic[k], RegexOptions.IgnoreCase);
                        }
                        catch(Exception ex)
                        {
                            Console.WriteLine(ex);
                        }
                        //nl = nl.Replace(k, _replacementDic[k]);
                    }
                    if(parsed)
                    {
                        nl = message.DateTime.ToString("yyyy-MM-dd HH:mm:ss.fff") + nl;
                    }
                    newLines.Add(nl);
                }
                message.Lines = newLines;
               // Console.WriteLine("Finished" + message.DateTime.ToString("yyyy-MM-dd HH:mm:ss,fff"));
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex);
            }
        }

        private static bool GetDateTimeFromString(string str, out DateTime dt)
        {
            dt = DateTime.MinValue;
            var parsed = str.Split(new string[] { " ", ",", "." }, StringSplitOptions.RemoveEmptyEntries);
            if (!parsed.Any() || parsed.Count()<3)
            {
                return false;
            }

            return DateTime.TryParse(parsed[0] + " " + parsed[1] + "." + parsed[2], out dt);
        }

        private static string replaceDateTime(string l)
        {
            DateTime dt;
            var res = GetDateTimeFromString(l, out dt);
            if(res==true)
            {
                var parsed = l.Split(new string[] { " ", ",", "." }, StringSplitOptions.RemoveEmptyEntries);
                var toReplace = parsed[0] + " " + parsed[1]+","+parsed[2];
                return l.Replace(toReplace, dt.Ticks.ToString());
            }
            return l;
            
        }

        private static void ReadMessage(StreamReader file)
        {
            string line;
            var message = new List<string>();
            Message currentMessage = null;
            var rows = 0;

            while ((line = file.ReadLine()) != null)
            {
                rows++;
                try
                {
                    var parsed = line.Split(new string[] { " ", ",", "." }, StringSplitOptions.RemoveEmptyEntries);
                    if (!parsed.Any())
                    {
                        continue;
                    }
                    
                    DateTime dt = DateTime.MinValue;
                    var res = GetDateTimeFromString(line, out dt);
                    
                    if (res == true)
                    {
                        _messagesToParse.Enqueue(currentMessage);
                        currentMessage = new Message { DateTime = dt };
                        //currentMessage = m;
                        currentMessage.Lines = new List<string> { line };
                        started = true;
                    }
                    else
                    {
                        if (currentMessage != null)
                        {
                            currentMessage.Lines.Add(line);
                        }
                    }
                }
                catch(Exception ex)
                {

                }
                
            }
            if (currentMessage != null)
            {
                _messagesToParse.Enqueue(currentMessage);
            }
            var stopped = 0;
        }

        private static void RewriteFile(string filename, string newFileName)
        {
            Console.WriteLine("Starting RewriteFile");
            DateTime start = DateTime.Now;
            System.IO.StreamReader file = new System.IO.StreamReader(filename);
            System.IO.StreamWriter newFile = new StreamWriter(newFileName);
            string line;
            while ((line = file.ReadLine()) != null)
            {
                foreach(var k in _inveseDic.Keys.Reverse())
                {
                    line = Regex.Replace(line, k, Regex.Escape(_inveseDic[k]), RegexOptions.IgnoreCase);
                    //line = line.Replace(k, _inveseDic[k]);                    
                }
                newFile.WriteLine(line);
            }

            newFile.Close();
            file.Close();

            var span = DateTime.Now - start;
            Console.WriteLine(string.Format("Finished RewriteFile within {0} seconds", span.TotalSeconds));
           
        }

    }
}
