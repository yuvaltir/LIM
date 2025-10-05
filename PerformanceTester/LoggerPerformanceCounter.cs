using log4net;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Configuration.Install;

namespace PerformanceTester
{
    class LoggerPerformanceCounter
    {
       

        private static readonly string CategoryName = "LIM.PerformanceCounters";
        private const String AverageDurationCounterName = "Average Request Processing Time";
        private const String AverageDurationBaseCounterName = "AverageDurationBaseCounterName";
        private const string TotalSentCounterName = "Total requests sent";
        private const string TotalFailedCounterName = "Total requests failed";
        private const string TotalSucceededCounterName = "Total requests Succeeded";
        private const string TotalSentCounterNamePerSecond = "Total requests sent per second";
        private const string WorkersCountCounterName = "Worker Count";
        private static readonly ILog Logger = LogManager.GetLogger("Logger Performance Counters");
        private static PerformanceCounterInstaller loggerPerformanceCounterInstaller;
        private static PerformanceCounterInstaller _PerformanceCounterInstaller;
                
        public static void DeleteCategory()
        {
            PerformanceCounterCategory.Delete(CategoryName);
        }


//For average duration counter

        public static PerformanceCounter GetAverageDurationCounter(string instanceName)
        {
            CreateCategory();
            return new PerformanceCounter(CategoryName, AverageDurationCounterName, instanceName, false);
        }


        public static PerformanceCounter GetAverageDurationBaseCounter(string instanceName)
        {
            CreateCategory();
            return new PerformanceCounter(CategoryName, AverageDurationBaseCounterName, instanceName, false);
        }

//For average duration counter


        public static PerformanceCounter GetTotalSentCounter(string instanceName)
        {
            CreateCategory();
            return new PerformanceCounter(CategoryName, TotalSentCounterName, instanceName, false);
        }

        public static PerformanceCounter GetTotalFailedCounter(string instanceName)
        {
            CreateCategory();
            return new PerformanceCounter(CategoryName, TotalFailedCounterName, instanceName, false);
        }
        public static PerformanceCounter GetTotalSucceededCounter(string instanceName)
        {
            CreateCategory();
            return new PerformanceCounter(CategoryName, TotalSucceededCounterName, instanceName, false);
        }

        public static PerformanceCounter GetTotalSentCounterPerSecond(string instanceName)
        {
            CreateCategory();
            return new PerformanceCounter(CategoryName, TotalSentCounterNamePerSecond, instanceName, false);
        }

        public static PerformanceCounter GetWorkersCountCounter(string instanceName)
        {
            CreateCategory();
            PerformanceCounter WorkersCountCounter = new PerformanceCounter(CategoryName, WorkersCountCounterName, instanceName, false);
            //WorkersCountCounter.RawValue = 0;
            return WorkersCountCounter;
        }



        public static void CreateCategory()
        {
            if (PerformanceCounterCategory.Exists(CategoryName)) return;
            _PerformanceCounterInstaller = InitPerfCounterInstaller();
            

          

            // Create the category.
            PerformanceCounterCategory.Create(_PerformanceCounterInstaller.CategoryName, _PerformanceCounterInstaller.CategoryHelp,
                _PerformanceCounterInstaller.CategoryType, _PerformanceCounterInstaller.Counters);

        }

        public static PerformanceCounterInstaller InitPerfCounterInstaller()
        {

            
            Logger.Debug("InitPerfCounterInstaller started");
            // var counterDataCollection = new CounterCreationDataCollection();

            loggerPerformanceCounterInstaller = new PerformanceCounterInstaller();
            Logger.Debug("InitPerfCounterInstaller object created");
            loggerPerformanceCounterInstaller.CategoryName = CategoryName;
            loggerPerformanceCounterInstaller.CategoryHelp = CategoryName;
            loggerPerformanceCounterInstaller.CategoryType = PerformanceCounterCategoryType.MultiInstance;



            // Add the counter(for duration.)
            var LoggerAverageProcessingTime = new CounterCreationData
            {
                CounterType = PerformanceCounterType.AverageTimer32,
                CounterName = AverageDurationCounterName
            };

            loggerPerformanceCounterInstaller.Counters.Add(LoggerAverageProcessingTime);

            // Add the base counter (for duration).
            var LoggerAverageProcessingTimeBase = new CounterCreationData
            {
                CounterType = PerformanceCounterType.AverageBase,
                CounterName = AverageDurationBaseCounterName
            };
            loggerPerformanceCounterInstaller.Counters.Add(LoggerAverageProcessingTimeBase);

            // Add the counter.(total sent)
            var LoggerTotalSentCounter = new CounterCreationData
            {
                CounterType = PerformanceCounterType.NumberOfItems32,
                CounterName = TotalSentCounterName
            };

            loggerPerformanceCounterInstaller.Counters.Add(LoggerTotalSentCounter);

            // Add the counter.(total failed)
            var LoggerTotalFailedCounter = new CounterCreationData
            {
                CounterType = PerformanceCounterType.NumberOfItems32,
                CounterName = TotalFailedCounterName
            };

            loggerPerformanceCounterInstaller.Counters.Add(LoggerTotalFailedCounter);


            // Add the counter.(total Succeeded)
            var LoggerTotalSucceededCounter = new CounterCreationData
            {
                CounterType = PerformanceCounterType.NumberOfItems32,
                CounterName = TotalSucceededCounterName
            };

            loggerPerformanceCounterInstaller.Counters.Add(LoggerTotalSucceededCounter);

            // Add the counter.(per second)
            var LoggerTotalSentCounterPerSecond = new CounterCreationData
            {
                CounterType = PerformanceCounterType.RateOfCountsPerSecond32,
                CounterName = TotalSentCounterNamePerSecond
            };

            loggerPerformanceCounterInstaller.Counters.Add(LoggerTotalSentCounterPerSecond);

            // Add the counter.(worker count)
            var LoggerWorkerCountCounter = new CounterCreationData
            {
                CounterType = PerformanceCounterType.NumberOfItems32,
                CounterName = WorkersCountCounterName
            };

            loggerPerformanceCounterInstaller.Counters.Add(LoggerWorkerCountCounter);
            loggerPerformanceCounterInstaller.UninstallAction = UninstallAction.Remove;
            
           return loggerPerformanceCounterInstaller;
            
        }



    }

}
