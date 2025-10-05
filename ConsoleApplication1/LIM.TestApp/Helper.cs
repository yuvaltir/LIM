using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LIM
{
    public class Helper
    {
        public static bool GetDateTimeFromString(string str, out DateTime dt)
        {
            dt = DateTime.MinValue;
            var parsed = str.Split(new string[] { " ", ",", "." }, StringSplitOptions.RemoveEmptyEntries);
            if (!parsed.Any() || parsed.Count() < 3)
            {
                return false;
            }
            
            return DateTime.TryParse(parsed[0] + " " + parsed[1] + "." + parsed[2], out dt);
        }

    }

    public static class ListExtension
    {
        public static void Shuffle<T>(this IList<T> list)
        {
            int n = list.Count;
            while (n > 1)
            {
                n--;
                int k = rng.Next(n + 1);
                T value = list[k];
                list[k] = list[n];
                list[n] = value;
            }
        }
        private static Random rng = new Random();  
    }
}
