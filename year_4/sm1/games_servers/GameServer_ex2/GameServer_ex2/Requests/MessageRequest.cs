using GameServer_ex2.Managers;
using GameServer_ex2.Models;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WebSocketSharp.Server;
using static System.Collections.Specialized.BitVector32;

namespace GameServer_ex2.Requests
{
    internal class MessageRequest
    {
        public static void Get(IWebSocketSession session, string data)
        {
            string session_id = session.ID;

            Console.WriteLine("\nMessageRequest. message from session ID: " + session_id);
            Console.WriteLine("MessageRequest. message data: " + data);

            Dictionary<string, object> ret = new Dictionary<string, object>();
            try
            {
                User curr_user = SessionsManager.Instance.GetUser(session_id);

                if (curr_user != null)
                {
                    JObject msg_data = JObject.Parse(data); //parsing string to Json
                    if (msg_data.ContainsKey("Service"))
                    {
                        //TODO: start game
                    }

                    else if (msg_data.ContainsKey("Msg"))
                    {//according to SC_LoginLogic.Btn_SearchingOpponent_SendMessage()
                     //this is the key we got for brodcasting msg in client game

                        BrodcastMessage(msg_data["Msg"].ToString());
                    }

                    //TODO: SEND BRODCAST TO ALL PLAYERS

                    else
                        Console.WriteLine("\nMessageRequest:No service was sent to session id " + session_id);



                }
                else
                    Console.WriteLine("\nMessageRequest: no user exist with session Id " + session_id);
            }
            catch (Exception e)
            {
                Console.WriteLine("\nMessageRequest: error " + e.Message);
            }

            string json_ret = JsonConvert.SerializeObject(data);
            SendMessage(session, json_ret);
        }

        private static bool SendMessage(IWebSocketSession session, string msg)
        {
            Console.WriteLine("\\nMessageRequest: SendMessage. send to session ID: " + session.ID);
            Console.WriteLine("MessageRequest: SendMessage. message: " + msg);

            if (session.ConnectionState == WebSocketSharp.WebSocketState.Open)
            {
                session.Context.WebSocket.Send(msg);
                return true;
            }
            return false;
        }

        private static void BrodcastMessage(string msg)
        {
            Console.WriteLine("\nMessageRequest: BrodcastMessage. send to everyone");
            Console.WriteLine("MessageRequest: BrodcastMessage. message: " + msg);
            Dictionary<string, User> temp_session = SessionsManager.Instance.UserSession;

            foreach (string sess in temp_session.Keys)
            {
                IWebSocketSession curr_session = temp_session["sess"].Session;
                if (curr_session.ConnectionState == WebSocketSharp.WebSocketState.Open)
                    curr_session.Context.WebSocket.Send(msg);
            }
                
        }
    }
}
