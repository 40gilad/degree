using GameServer_ex2.Requests;
using System;
using System.Linq;
using WebSocketSharp;
using WebSocketSharp.Server;

namespace GameServer_ex2.Handlers
{
    internal class GameServerHandler:WebSocketBehavior
    {
        protected override void OnOpen()
        {
            Console.WriteLine("\nOnOpen " + ID);
            try
            {
                
                if (Context.QueryString.AllKeys.Contains("data"))
                {
                    ConnectionRequest.Get(Sessions[ID], Context.QueryString["data"]);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("\nOnOpen Failed. Error: "+e.Message);
                Sessions.CloseSession(ID);
            }
        }

        protected override void OnClose(CloseEventArgs e)
        {
            Console.WriteLine("\nOnClose " + ID);
            CloseConnectionRequest.RemoveConnection(ID);
        }

        protected override void OnError(ErrorEventArgs e)
        {

        }

        protected override void OnMessage(MessageEventArgs e)
        {

        }
    }

}
