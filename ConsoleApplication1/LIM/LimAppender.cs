using log4net.Appender;
using log4net.Core;
using log4net.Layout.Pattern;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LIM
{
    public sealed class LineCounterPatternConverter : PatternLayoutConverter
    {
        private static int _counter = 0;

        protected override void Convert(TextWriter writer, LoggingEvent loggingEvent)
        {
            //var counter = System.Threading.Interlocked.Increment(ref _counter);
            //writer.Write(loggingEvent.);
        }
    }

    public class LimAppender : RollingFileAppender
    {

        protected override void Append(log4net.Core.LoggingEvent loggingEvent)
        {                        
            var msg = loggingEvent.MessageObject.ToString();
            string newStr = "", oldStr="";
            try
            {
                //var res = Importer.add(1, 3);
                 newStr = Importer.replace(msg, msg.Length);
                 oldStr = Importer.replaceBack(newStr, newStr.Length);
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
            var loggingEvent1 = new LoggingEvent(new LoggingEventData
            {
                Domain = loggingEvent.Domain,
                ExceptionString = loggingEvent.GetExceptionString(),
                Identity = loggingEvent.Identity,
                Level = loggingEvent.Level,
                LocationInfo = loggingEvent.LocationInformation,
                LoggerName = loggingEvent.LoggerName,
                Message = oldStr,
                Properties = loggingEvent.Properties,
                ThreadName = loggingEvent.ThreadName,
                TimeStamp = loggingEvent.TimeStamp,
                UserName = loggingEvent.UserName

            });
            //loggingEvent.MessageObject = after;
            //loggingEvent1 = new log4net.Core.LoggingEvent(loggingEvent. ExceptionObject = loggingEvent.ExceptionObject,
            //Fix = loggingEvent.Fix,
            //Level = loggingEvent.Level,
            //LocationInformation = loggingEvent.LocationInformation,
            //Properties = loggingEvent.Properties,
            //Repository = loggingEvent.Repository,
            //TimeStamp = loggingEvent.TimeStamp,
            //}
            //base.Append(loggingEvent);
            //Console.WriteLine("weqweqweqwewqe");
           //File.AppendAllText(_file,"qweqweqwe");
            base.Append(loggingEvent1);
            
        }

        //private string _file;
        //public string file { get { return _file; } set { File.CreateText(value); _file = value; } }

        /// <summary>
        /// This appender requires a <see cref="Layout"/> to be set.
        /// </summary>
        override protected bool RequiresLayout
        {
            get { return false; }
        }
    }

}
