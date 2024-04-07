using GameServer_ex2.Threads;
using GameServer_ex2.Threads;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameServer_ex2.Managers
{
    public class RoomsManager
    {
        private Dictionary<string, GameThread> activeRooms;

        #region Singleton
        private static RoomsManager instance;

        internal static RoomsManager Instance
        {
            get
            {
                if (instance == null)
                    instance = new RoomsManager();
                return instance;
            }
        }
        #endregion

        public RoomsManager()
        {
            activeRooms = new Dictionary<string, GameThread>();
        }

        public void AddRoom(string MatchId, GameThread Room)
        {
            if (activeRooms == null)
                activeRooms = new Dictionary<string, GameThread>();

            if (activeRooms.ContainsKey(MatchId))
                activeRooms[MatchId] = Room;
            else activeRooms.Add(MatchId, Room);
        }

        public void RemoveRoom(string MatchId)
        {
            if (activeRooms != null && activeRooms.ContainsKey(MatchId))
                activeRooms.Remove(MatchId);
        }

        public GameThread GetRoom(string MatchId)
        {
            if (activeRooms != null && activeRooms.ContainsKey(MatchId))
                return activeRooms[MatchId];
            return null;
        }

        public bool IsRoomExist(string MatchId)
        {
            if (GetRoom(MatchId) != null)
                return true;
            else return false;
        }
    }
}
