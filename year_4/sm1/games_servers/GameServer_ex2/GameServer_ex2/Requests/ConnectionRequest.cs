using GameServer_ex2.Models;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using WebSocketSharp.Server;
using GameServer_ex2.Managers

namespace GameServer_ex2.Requests
{
    internal class ConnectionRequest
    {
        public static void Get(IWebSocketSession session, string data)
        {
            Console.WriteLine("ConnectionRequest to Id: " + data);
            Dictionary<string, object> ret = new Dictionary<string, object>();

            try
            {
                JObject user_data = JObject.Parse(data);

                if (user_data != null && user_data.ContainsKey("UserId"))
                {
                    string uid = user_data["UserId"].ToString();
                    User curr_user = new User(uid: uid, sess: session);
                    curr_user.SetMatching(); // set User state to matching

                    SessionsManager.Instance.AddUser(curr_user);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("ConnectionRequest Error: " + e.Message);
            }
        }
    }
}
