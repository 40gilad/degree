using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameServer_ex2.Models
{
    internal class MatchData
    {
        private Dictionary<string, SearchingData> matched_players_data;//will hold {user_id : searching_data}
        public Dictionary<string, SearchingData> MatchedPlayersData { get => matched_players_data;}

        private int match_id;
        public int MatchId { get => match_id; }

        private string match_time;
        public string MatchTime { get { return match_time; } }


        public MatchData(List<SearchingData> search_data,int curr_match_id)
        {
            //MatchedPlayersData=......
            match_id=curr_match_id;
            match_time = DateTime.UtcNow.ToString();
            foreach (SearchingData sd in search_data)
            {
                sd.IsPlayerReady = false;
                matched_players_data.Add(sd.UserID, sd);
            }


        }
    }
}
