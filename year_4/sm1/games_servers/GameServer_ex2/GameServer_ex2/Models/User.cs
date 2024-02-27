using System;
using WebSocketSharp.Server;
using static GameServer_ex2.Globals.GlobalEnums;

namespace GameServer_ex2.Models
{
    internal class User
    {
        public enum UserState { Idle = 100, Matching = 101, Playing = 102 };

        private string id;
        public string UserId { get { return id; }  }


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
        }

        public WebSocketSharp.WebSocketState GetConnectionState()
        {
            return Session.ConnectionState;
        }

        public void CloseConnection(CloseConnectionCode close_code,string message)
        {
            Session.Context.WebSocket.Close();
        }

    }
}
