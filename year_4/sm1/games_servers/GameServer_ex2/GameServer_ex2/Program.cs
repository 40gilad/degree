using GameServer_ex2.Handlers;
using System;
using WebSocketSharp.Server;


namespace GameServer_ex2
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string server_url = Globals.GlobalVariables.ServerUrl;
            WebSocketServer server = new WebSocketServer(server_url);
            server.AddWebSocketService<GameServerHandler>("/GameServer");
            server.Start();
            Console.WriteLine("\nMain Live Server "+ server_url);
            Console.ReadKey();
            server.Stop();
        }
    }
}
