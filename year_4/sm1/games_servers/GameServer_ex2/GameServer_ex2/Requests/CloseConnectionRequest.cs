using GameServer_ex2.Managers;
using System;

namespace GameServer_ex2.Requests
{
    internal class CloseConnectionRequest
    {
        public static void RemoveConnection(string SessionID)
        {
            string uid = SessionsManager.Instance.UserSession[SessionID].UserId;
            if (!SearchingManager.Instance.RemoveFromSearchingList(uid))
                Console.WriteLine(
                    "\nCloseConnectionRequest: uid of session ID " + SessionID + "is null");

            else Console.WriteLine(
                "\nCloseConnectionRequest: User ID " + uid + " of session ID " + SessionID +
                " is closed"
                );
        }
    }
}
