using log4net;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PerformanceTester
{
    public partial class Form1 : Form
    {
        private readonly ILog Logger;
        private DateTime _end, _start;
        private delegate void IncrementProgressDel(int steps);
        
        public Form1()
        {
            log4net.Config.XmlConfigurator.Configure();
            
            InitializeComponent();
            
            Logger = LogManager.GetLogger(this.GetType());            
            LoggerPerformanceCounter.CreateCategory();
        }        

        private void ParseInputs()
        {
            _start = DateTime.Now;
            lStart.Text = _start.ToString("dd/MM/yy HH:mm:ss");
            _end = _start.AddDays((int)nudDays.Value).AddHours((int)nudHours.Value).AddMinutes((int)nudMins.Value);
            lEnd.Text = _end.ToString("dd/MM/yy HH:mm:ss");
        }

        private void SetMaxProgress()
        {
            progressBar1.Maximum = (60*((24 * (int)nudDays.Value) + (int)nudHours.Value))+(int)nudMins.Value;
            progressBar1.Step = 1;
        }

        private void IncrementProgress(int steps)
        {
            if(progressBar1.InvokeRequired)
            {
                var del = new IncrementProgressDel(IncrementProgress);
                progressBar1.BeginInvoke(del, steps);                
            }
            else
            {
                if (steps <= progressBar1.Maximum)
                {
                    progressBar1.Value = steps;
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            ParseInputs();
            SetMaxProgress();
            var input = textBox1.Text;
            if(!File.Exists(input))
            {
                return;
            }
            var alllines =  File.ReadAllLines(input);
            var messages = new List<string>();
            var currentMessage = new StringBuilder();
            foreach(var l in alllines)
            {
                if(l==string.Empty)
                {
                    messages.Add(currentMessage.ToString());
                    currentMessage = new StringBuilder();                    
                }
                else
                {
                    currentMessage.AppendLine(l);
                }
            }

            Task.Factory.StartNew(() => LogForAWhile(messages));
        }

        private void LogForAWhile(List<string> messages)
        {
            while (DateTime.Now < _end)
            {
                var sw = Stopwatch.StartNew();
                foreach (var m in messages)
                {                    
                    LogMessage(m);
                }
                sw.Stop();
                IncrementByAverageDurationCounter(sw.ElapsedTicks, PerformanceCounterInstanceName.LoggerInstanceName); // time per request
                IncrementAverageDurationBaseCounter(PerformanceCounterInstanceName.LoggerInstanceName); // request count
                var minutesPassed = (int)(DateTime.Now-_start).TotalMinutes;
                if (minutesPassed > 0)
                {
                    IncrementProgress(minutesPassed);
                }
            }
        }
         

        private void LogMessage(string mesasge)
        {           
            Logger.Info(mesasge);                     
        }

        static void IncrementByAverageDurationCounter(long elapsedTicks, string instance)
        {

            var ps = LoggerPerformanceCounter.GetAverageDurationCounter(instance);
            ps.IncrementBy(elapsedTicks);
            ps.Close();

        }

        static void IncrementAverageDurationBaseCounter(string instance)
        {

            var ps = LoggerPerformanceCounter.GetAverageDurationBaseCounter(instance);
            ps.Increment();
            ps.Close();

        }

        public struct PerformanceCounterInstanceName
        {
            public const string LoggerInstanceName = "Logger";            
        }
    }
}
