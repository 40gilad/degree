using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameServer_ex2.Globals
{
    internal class GlobalVariables
    {
        private static string server_url="ws://localhost:7890";
        public static string ServerUrl { get { return server_url; } }

        private static int _turnTime = 10;
        public static int TurnTime { get { return _turnTime; } }
    }
}
