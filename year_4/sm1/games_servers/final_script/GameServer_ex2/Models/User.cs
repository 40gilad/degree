using System;
using WebSocketSharp.Server;
using static GameServer_ex2.Globals.GlobalEnums;

namespace GameServer_ex2.Models
{
    public class User
    {
        public enum UserState { Idle = 100, Matching = 101, PrePlay=102, Playing = 103 };

        private string id;
        public string UserId { get { return id; }  }

        private string match_id;
        public string MatchId { get => match_id; set => match_id = value; }

        private IWebSocketSession session;
        public IWebSocketSession Session { get { return session; }  }


        private UserState curr_state;
        public UserState CurrState { get { return curr_state; }  set { curr_state = value; } }
        public void SetMatching()
        {
            curr_state = UserState.Matching;
            matching_date = DateTime.Now;
        }

        public void SetPlaying()
        {
            curr_state=UserState.Playing;
        }

        private DateTime matching_date;
        public DateTime MatchDate { get { return matching_date; }  }

        public User(string uid, IWebSocketSession sess)
        {
            id = uid;
            session = sess;
            curr_state = UserState.Idle; //first connection. Idle is initial state
            match_id = String.Empty;
        }

        public WebSocketSharp.WebSocketState GetConnectionState()
        {
            return Session.ConnectionState;
        }

        public void CloseConnection(CloseConnectionCode close_code,string message)
        {
            Session.Context.WebSocket.Close((ushort)close_code,message);
        }

        public bool IsUserLiveWithSession()
        {
            //check if user has open socket with session

            if (Session != null && Session.ConnectionState == WebSocketSharp.WebSocketState.Open)
                return true;
            return false;
        }

        public void SendMessage(string msg)
        {
            try
            {
                if (IsUserLiveWithSession())
                    Session.Context.WebSocket.Send(msg);
                else Console.WriteLine("\nUser " + id + "is not live with session (Socket is not open)");

            }
            catch(Exception e)
            {
                Console.WriteLine("\nUser "+ id+" SendMessage: "+e.ToString());
            }
        }
    }
}
