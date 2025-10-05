using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LIM
{
    public class LogMessage
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

        private LimRes _limRes;

        public LimRes LimRes
        {
            get { return _limRes; }
            set { _limRes = value; }
        }
    }
}
