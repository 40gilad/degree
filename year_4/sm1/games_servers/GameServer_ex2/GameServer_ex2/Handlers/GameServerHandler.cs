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
        }

        protected override void OnClose(CloseEventArgs e)
        {
            Console.WriteLine("OnClose " + ID);

        }

        protected override void OnError(ErrorEventArgs e)
        {
            Console.WriteLine("OnError " + ID);

        }

        protected override void OnMessage(MessageEventArgs e)
        {
            Console.WriteLine("OnMessage " + ID);

        }
    }

}
