using GameServerShenkar.Managers;
using GameServerShenkar.Models;
using GameServerShenkar.Threads;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Remoting.Messaging;
using System.Text;
using System.Threading.Tasks;

namespace GameServerShenkar.Requests
{
    internal class LiveRoomInfoRequest
    {
        public static Dictionary<string, object> Get(User CurUser, Dictionary<string, object> Details)
        {
            Dictionary<string, object> response = new Dictionary<string, object>();
            if (Details.ContainsKey("RoomId"))
            {
                response.Add("Response", "GetLiveRoomInfo");
                response.Add("RoomData", "GetLiveRoomInfo");
                response.Add("RoomProperties", "GetLiveRoomInfo");
                response.Add("Users", "GetLiveRoomInfo");

                // Users list
                GameThread room= RoomsManager.Instance.GetRoomByRoomId(Details["RoomId"].ToString());
                Dictionary<string, User> uid_user_pair = room.Users;
                List<string> users = new List<string>();
                foreach (KeyValuePair<string,User> pair in uid_user_pair)
                    users.Add(pair.Key);
              
            }
            else
                response.Add("Response", "GetLiveRoomInfo");
            return response;

        }
    }
}
