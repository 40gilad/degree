using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameServer_ex2.Models
{
    public class SearchingData
    {
        private string uid;
        public string UserID {get { return uid; } }

        private int player_rating;
        public int PlayerRating { get { return player_rating; } }

        public bool is_player_ready;
        public bool IsPlayerReady {get { return is_player_ready;} set { is_player_ready = value; } }

        public SearchingData(string _uid,int rating)
        {
            uid = _uid;
            player_rating=rating;
            is_player_ready = false;
        }
    }
}
