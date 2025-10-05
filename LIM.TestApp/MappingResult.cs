using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LIM
{
    public class MappingResult
    {
        private int _messageCount;

        public int MessageCount
        {
            get { return _messageCount; }
            set { _messageCount = value; }
        }

        private double _avgMessageLimInMillisec;

        public double AvgMessageLimInMillisec
        {
            get { return _avgMessageLimInMillisec; }
            set { _avgMessageLimInMillisec = value; }
        }

        private double _avgMessageMilInMillisec;

        public double AvgMessageMilInMillisec
        {
            get { return _avgMessageMilInMillisec; }
            set { _avgMessageMilInMillisec = value; }
        }

        private double _avgMessageSize;

        public double AvgMessageSize
        {
            get { return _avgMessageSize; }
            set { _avgMessageSize = value; }
        }

        private double _avgLimMessageSize;

        public double AvgLimMessageSize
        {
            get { return _avgLimMessageSize; }
            set { _avgLimMessageSize = value; }
        }

        private double _avgKbLimTime;

        public double AvgKbLimTime
        {
            get { return _avgKbLimTime; }
            set { _avgKbLimTime = value; }
        }
        
        private double _avgKbMilTime;

        public double AvgKbMilTime
        {
            get { return _avgKbMilTime; }
            set { _avgKbMilTime = value; }
        }       

        private long _fileSizeInKb;

        public long FileSizeInKb
        {
            get { return _fileSizeInKb; }
            set { _fileSizeInKb = value; }
        }

        private long _limFileSizeInKb;

        public long LimFileSizeInKb
        {
            get { return _limFileSizeInKb; }
            set { _limFileSizeInKb = value; }
        }
    }
}
