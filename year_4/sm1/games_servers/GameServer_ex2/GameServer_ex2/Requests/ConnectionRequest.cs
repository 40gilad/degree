using GameServer_ex2.Models;
using Newtonsoft.Json.Linq;
using System;
using GameServer_ex2.Services;
using WebSocketSharp.Server;
using GameServer_ex2.Managers;
using static GameServer_ex2.Globals.GlobalEnums;

namespace GameServer_ex2.Requests
{
    internal class ConnectionRequest
    {
        public static void Get(IWebSocketSession session, string data)
        {
            Console.WriteLine("\nConnectionRequest. Open connection with session ID: " + session.ID);
            
            try
            {
                JObject user_data = JObject.Parse(data); //parsing string to Json

                if (user_data != null && user_data.ContainsKey("UserId"))
                {
                    string uid = user_data["UserId"].ToString();
                    User curr_user = new User(uid: uid, sess: session);
                    curr_user.SetMatching(); // set User state to matching
                    SessionsManager.Instance.AddUser(curr_user);
                    int curr_user_rating=RedisService.GetUserRating(uid: uid);

                    if (curr_user_rating<0)
                        Console.WriteLine(
                            "\nConnectionRequest: Error occured. User "
                            + uid +" rating returned "+curr_user_rating
                            );

                    if (SearchingManager.Instance.AddToSearchingDict(uid: uid, rating: curr_user_rating))
                        Console.WriteLine(
                            "\nConnectionRequest: AddToSearchingList returned false for User "
                            + uid + " with rating "+ curr_user_rating
                            );


                }
                else
                {
                    session.Context.WebSocket.Close((ushort)CloseConnectionCode.MissingUserId,"OnOpen connection -> Get: User Id is missing");
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("\nConnectionRequest Error: " + e.Message);
            }
        }


    }
}
