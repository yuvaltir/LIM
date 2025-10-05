using log4net;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace LIM.Server.Map.Initiator
{
    public class Compiler
    {
        private static readonly ILog Logger = LogManager.GetLogger(MethodBase.GetCurrentMethod().DeclaringType);

        private string _msBuildLocation;
        public Compiler(string MsBuildLocation=@"C:\Program Files (x86)\MSBuild\12.0\Bin")
        {
            _msBuildLocation = MsBuildLocation;
        }

        private bool GetProjectFile(string folder, out string projName)
        {
            if(folder.EndsWith("\\"))
            {
               folder= folder.Remove(folder.Length-2);
            }
             projName = string.Empty;
           
            if(!Directory.Exists(folder))
            {
                Logger.ErrorFormat("Cannot locate folder {0}", folder);
                return false;
            }

            var projFIles = Directory.GetFiles(folder, "*.vcxproj");
            if(projFIles.Count()>=1)
            {
                projName = projFIles.First();
                return true;
            }
            return false;           
        }

        public bool Compile(string projFolder)
        {
            bool res = false;
            string projFileFullName;
            GetProjectFile(projFolder, out projFileFullName);
            Logger.DebugFormat("About to compile {0}",projFileFullName);
            ProcessStartInfo startInfo = new ProcessStartInfo{
                FileName = string.Format(@"{0}\MsBuild.exe",_msBuildLocation),
                Arguments = string.Format("\"{0}\" /p:configuration=release",projFileFullName),
                UseShellExecute = false,
                RedirectStandardOutput = true,
                CreateNoWindow = true
            };
            var proc = Process.Start(startInfo);
            while (!proc.StandardOutput.EndOfStream)
            {
                string line = proc.StandardOutput.ReadLine();
                if(line.Contains("Build succeeded."))
                {
                    res = true;
                }                
            }
            proc.WaitForExit();
            return res;
            
        }
    }
}
