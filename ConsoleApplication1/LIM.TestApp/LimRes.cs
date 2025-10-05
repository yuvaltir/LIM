using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LIM
{
    public class LimRes
    {
        private long _originalMessageSize;

        public long OriginalMessageSize
        {
            get { return _originalMessageSize; }
            set { _originalMessageSize = value; }
        }

        private long _limMessageSize;

        public long LimMessageSize
        {
            get { return _limMessageSize; }
            set { _limMessageSize = value; }
        }

        private TimeSpan _limDuration;

        public TimeSpan LimDuration
        {
            get { return _limDuration; }
            set { _limDuration = value; }
        }
    }
}
