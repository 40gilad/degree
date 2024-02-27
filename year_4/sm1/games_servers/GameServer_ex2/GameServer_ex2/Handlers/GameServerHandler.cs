using GameServer_ex2.Requests;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WebSocketSharp;
using WebSocketSharp.Server;

namespace GameServer_ex2.Handlers
{
    internal class GameServerHandler:WebSocketBehavior
    {
        protected override void OnOpen()
        {
            Console.WriteLine("OnOpen " + ID);
            try
            {
                
                if (Context.QueryString.AllKeys.Contains("data"))
                {
                    ConnectionRequest.Get(Sessions[ID], Context.QueryString["data"]);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("OnOpen Failed. Error: "+e.Message);
                Sessions.CloseSession(ID);
            }
        }

        protected override void OnClose(CloseEventArgs e)
        {
            Console.WriteLine("OnClose " + ID);

        }

        protected override void OnError(ErrorEventArgs e)
        {

        }

        protected override void OnMessage(MessageEventArgs e)
        {

        }
    }

}
