using System;
using System.Diagnostics;
using System.Text.RegularExpressions;

namespace GameServer_ex2.Utils
{
    public class UtilFunctions
    {

        public static int GetRandomNumber(int min, int max)
        {
            var seed = Convert.ToInt32(Regex.Match(Guid.NewGuid().ToString(), @"\d+").Value);
            return new Random(seed).Next(min, max);
        }

        public static int GetExceptionLine(Exception _E)
        {
            try
            {
                var st = new StackTrace(_E, true);
                var frame = st.GetFrame(1);
                return frame.GetFileLineNumber();
            }
            catch (Exception) { }
            return -1;
        }

        public static string GetUtcTime()
        {
            string _date = DateTime.UtcNow.Year + "-" + DateTime.UtcNow.Month + "-" + DateTime.UtcNow.Day;
            _date += " " + DateTime.UtcNow.Hour + ":" + DateTime.UtcNow.Minute + ":" + DateTime.UtcNow.Second;
            return _date;
        }

    }
}
