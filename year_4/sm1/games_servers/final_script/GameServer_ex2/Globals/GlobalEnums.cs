using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameServer_ex2.Globals
{
    public class GlobalEnums
    {
        public enum CloseConnectionCode { Unknown= 100,DuplicateConnection=101, MissingUserId=102};
        public enum ErrorCodes
        {
            Unknown = 3000, MissingMatchId = 3001, RoomClosed = 3002, RoomDoesntExist = 3003,
            MissingVariables = 3004, NotPlayerTurn = 3005, MissingVaribles = 3006
        };
    }
}
