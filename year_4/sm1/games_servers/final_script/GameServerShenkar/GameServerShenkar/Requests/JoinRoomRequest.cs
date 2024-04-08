using GameServerShenkar.Managers;
using GameServerShenkar.Models;
using GameServerShenkar.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace GameServerShenkar.Requests
{
    internal class JoinRoomRequest
    {
        public static Dictionary<string, object> Get(User CurUser, Dictionary<string, object> Details)
        {
            Dictionary<string, object> response = new Dictionary<string, object>();
            /*
             *             {"Service", "JoinRoom"},
                            {"RoomId", roomId}
            */
            response.Add("IsSuccess", false);
            if (Details.ContainsKey("RoomId"))
            {
                string MatchId = RoomsManager.Instance.MatchRoomId["RoomId"];
                response.Add("Response", "JoinRoom");
                response.Add("RoomId", Details["RoomId"]);

                if (RoomsManager.Instance.GetRoom(MatchId.ToString()).AddPlayer(CurUser.UserId))
                    response["IsSuccess"]= true;
                    
                try
                {
                    MatchData curMatchData = MatchingManager.Instance.GetMatchingData(MatchId);
                    if (curMatchData != null)
                    {
                        curMatchData.ChangePlayerReady(CurUser.UserId, true);
                        if (curMatchData.IsAllReady())
                        {
                            MatchingManager.Instance.RemoveFromMatchingData(MatchId);
                            /*start game? */
                        }
                        else Console.WriteLine("Waiting for more players");
                    }
                }
                catch (Exception e) { }
            }
            else
                response.Add("Response", null);
            return response;
        }
    }
}
