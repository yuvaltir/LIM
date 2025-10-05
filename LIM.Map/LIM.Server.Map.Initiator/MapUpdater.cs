using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using log4net;
using System.Reflection;
[assembly: log4net.Config.XmlConfigurator(Watch = true)]

namespace LIM.Server.Map.Initiator
{
    public class MapUpdater
    {
        private static readonly ILog Logger = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);

        private List<string> _allMapLines = new List<string>();

        private Dictionary<string, string> _mapDic;

        private string _seperator;

        public MapUpdater(Dictionary<string,string> mapDic, string seperator = "~", string sourseFolder="LIM.DAWG.Map")
        {
            _sourceLocation = sourseFolder;
            _mapDic = mapDic;
            _seperator = seperator;
        }

        private readonly string MapFileName = "map.cpp";

        private readonly string MethodFirstLine = "void FillMapWithvalue()";

        private string _sourceLocation;

        private bool VerifyLocation(out string mapFileFullPath)
        {
            mapFileFullPath = string.Empty;
            if (!Directory.Exists(_sourceLocation))
            {
                var currentFolder = Assembly.GetExecutingAssembly().Location;

                var location = Directory.GetParent(currentFolder);

                var parent = Directory.GetParent(Directory.GetParent(location.FullName).ToString());

                _sourceLocation = parent + @"\" + _sourceLocation;
                if (!Directory.Exists(_sourceLocation))
                {
                    Logger.ErrorFormat("could not find directory: {0}", _sourceLocation);
                    return false;
                }
            }

            var fileName = string.Format("{0}\\{1}", _sourceLocation, MapFileName);
            if (!File.Exists(fileName))
            {
                Logger.ErrorFormat("could not find file: {0}", fileName);
                return false;
            }
            mapFileFullPath = fileName;

            return true;
        }

        /// <summary>
        /// Mapping dictionary has the short strings as keys and the originals as values
        /// </summary>
        /// <param name="fullFileName"></param>
        /// <param name="mappings"></param>
        /// <param name="seperatingChar"></param>
        private void AppendMapping(string fullFileName, Dictionary<string, string> mappings, string seperatingChar)
        {
            _allMapLines = File.ReadAllLines(fullFileName).ToList();

            RemoveExistingMapping(_allMapLines);
            var i = 0;

            _allMapLines.Add(Environment.NewLine);
            _allMapLines.Add(MethodFirstLine);
            _allMapLines.Add("{" + Environment.NewLine);
            foreach (var kv in mappings.OrderBy(kv=>kv.Value))
            {
                _allMapLines.Add("\t" + "_values.push_back(\"" + kv.Key + "\");" + Environment.NewLine);
            }
            foreach (var kv in mappings.OrderBy(kv => kv.Value))
            {
                _allMapLines.Add("\t" + "dawg_builder.Insert(\"" + kv.Value.Replace("\"","\\\"").ToUpper() + "\", " + i++ + ");" + Environment.NewLine);
            }

            _allMapLines.Add("\t" + "dawg_builder.Finish(&dawg);" + Environment.NewLine);
            _allMapLines.Add("\t" + "dawgdic::DictionaryBuilder::Build(dawg, &dawg_dic);" + Environment.NewLine);

            i = 0;
            foreach (var kv in mappings.OrderBy(kv => kv.Key))
            {
                _allMapLines.Add("\t" + "_valuesReverse.push_back(\"" + kv.Value.Replace("\"", "\\\"").ToUpper() + "\");" + Environment.NewLine);
            }

            foreach (var kv in mappings.OrderBy(kv => kv.Key))
            {
                _allMapLines.Add("\t" + "dawg_builderReverse.Insert(\"" + kv.Key + "\", " + i++ + ");" + Environment.NewLine);
            }

            _allMapLines.Add("\t" + "dawg_builderReverse.Finish(&dawgReverse);" + Environment.NewLine);
            _allMapLines.Add("\t" + "dawgdic::DictionaryBuilder::Build(dawgReverse, &dawg_dicReverse);" + Environment.NewLine);
            _allMapLines.Add("}");

            WriteAllLinesToFile(fullFileName, _allMapLines);
        }

        private void RemoveExistingMapping(List<string> allMapLines)
        {
            var found = false;
            var i = 0;
            var totalLines = allMapLines.Count;
            foreach(var l in allMapLines)
            {
                if (l.Contains(this.MethodFirstLine))
                {
                    found = true;
                    break;
                }
                else
                {
                    i++;
                }
            }

           if(found==true)
           {
               allMapLines.RemoveRange(i, totalLines - i);
           }
        }

        private bool WriteAllLinesToFile(string fullFileName, List<string> newLines)
        {
            if(!File.Exists(fullFileName))
            {
                Logger.ErrorFormat("Could not find file {0}", fullFileName);
                return false;
            }
            File.Delete(fullFileName);
            File.WriteAllLines(fullFileName, _allMapLines);
            return true;
        }

        public void UpdateMap()
        {
            string fullFileName;
            VerifyLocation(out fullFileName);
            AppendMapping(fullFileName, _mapDic, _seperator);
        }

        public void CompileAssembly()
        {

        }
    }
}
