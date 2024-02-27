using GameServer_ex2.Models;
using System.Collections.Generic;
using static GameServer_ex2.Globals.GlobalEnums;


namespace GameServer_ex2.Managers
{
    internal class SessionsManager
    {
        private Dictionary<string, User> user_session; // will hold 2 keys for each user. session id -> user and user_id -> user
        public Dictionary<string, User> UserSession { get { return user_session; } }

        #region Singleton
        private static SessionsManager instance;
        public static SessionsManager Instance
        {
            get
            {
                if (instance == null)
                    instance = new SessionsManager();
                return instance;
            }
        }
        #endregion

        public SessionsManager()
        {
            user_session = new Dictionary<string, User>();
        }

        public void AddUser(User user)
        {
            if (user_session == null)
                user_session = new Dictionary<string, User>();

            if (user_session.ContainsKey(user.UserId))
            { //user already have session.

                User curr_user = user_session[user.UserId];

                if (curr_user.GetConnectionState() == WebSocketSharp.WebSocketState.Open)
                {//user session is open. need to close it so user wond have 2 connections.
                    curr_user.CloseConnection(
                        close_code: CloseConnectionCode.DuplicateConnection,message:"Duplicate connection were found"
                        );

                    user_session.Remove(curr_user.Session.ID);
                    user_session[user.UserId] = user;
                }
            }

            else
                user_session.Add(user.UserId, user);
            if (user_session.ContainsKey(user.Session.ID))
                user_session[user.Session.ID] = user;
            else user_session.Add(user.Session.ID,user)
        }

    }
}
