using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LIM
{
    public class LogLine
    {
        string _prefix = string.Empty;

        public string Prefix
        {
            get { return _prefix; }
            set { _prefix = value; }
        }

        private string _text;

        public string Text
        {
            get { return _text; }
            set { _text = value; }
        }

        public string WholeLine
        {
            get { return string.Format("{0}{1}", _prefix,_text);}
        }
    }

    public class LogMessage
    {
        DateTime _dateTime;

        public DateTime DateTime
        {
            get { return _dateTime; }
            set { _dateTime = value; }
        }

        List<LogLine> _lines;

        public List<LogLine> Lines
        {
            get { return _lines; }
            set { _lines = value; }
        }

        private LimRes _limRes = new LimRes();

        public LimRes LimRes
        {
            get { return _limRes; }
            set { _limRes = value; }
        }

        public override string ToString()
        {
            return Lines.Any() ? Lines.First().Text : "empty";
        }
    }
}
