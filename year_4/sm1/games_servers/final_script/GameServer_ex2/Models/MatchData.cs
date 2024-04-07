using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameServer_ex2.Models
{
    public class MatchData
    {
        private Dictionary<string, SearchingData> matched_players_data;//will hold {user_id : searching_data}
        public Dictionary<string, SearchingData> MatchedPlayersData { get => matched_players_data;}

        private int match_id;
        public int MatchId { get => match_id; }

        private string match_time;
        public string MatchTime { get { return match_time; } }


        public MatchData(List<SearchingData> search_data,int curr_match_id)
        {
            if (matched_players_data == null)
                matched_players_data = new Dictionary<string, SearchingData>();
            match_id=curr_match_id;
            match_time = DateTime.UtcNow.ToString();
            foreach (SearchingData sd in search_data)
            {
                sd.IsPlayerReady = false;
                matched_players_data.Add(sd.UserID, sd);
            }


        }
        public void ChangePlayerReady(string UserId, bool IsReady)
        {
            if (matched_players_data.ContainsKey(UserId))
                matched_players_data[UserId].IsPlayerReady = IsReady;
        }

        public bool IsAllReady()
        {
            foreach (string userId in matched_players_data.Keys)
            {
                if (matched_players_data[userId].IsPlayerReady == false)
                    return false;
            }
            return true;
        }
    }
}
