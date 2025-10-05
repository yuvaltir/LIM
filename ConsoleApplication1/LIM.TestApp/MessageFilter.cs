using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LIM
{
    public class MessageFilter
    {
        private int _ignoreStart;

        public int IgnoreStart
        {
            get { return _ignoreStart; }
            set { _ignoreStart = value; }
        }
        private string _dtFormat;

        public string DtFormat
        {
            get { return _dtFormat; }
            set { _dtFormat = value; }
        }
        private int _ignoreEnd;

        public int IgnoreEnd
        {
            get { return _ignoreEnd; }
            set { _ignoreEnd = value; }
        }
        private string _ignoreFrom;

        public string IgnoreFrom
        {
            get { return _ignoreFrom; }
            set { _ignoreFrom = value; }
        }
        private string _ignoreTo;

        public string IgnoreTo
        {
            get { return _ignoreTo; }
            set { _ignoreTo = value; }
        }
    }
}
