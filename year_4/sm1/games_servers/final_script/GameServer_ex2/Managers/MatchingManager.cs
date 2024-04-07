using GameServer_ex2.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameServer_ex2.Managers
{
    public class MatchingManager
    {
        private Dictionary<string, MatchData> all_matchings;

        #region Singleton
        private static MatchingManager instance;
        public static MatchingManager Instance
        {
            get
            {
                if (instance == null)
                    instance = new MatchingManager();
                return instance;
            }
        }
        #endregion

        public MatchingManager()
        {
            if (all_matchings == null)
                all_matchings = new Dictionary<string, MatchData>();
        }

        public bool AddMatching(MatchData match)
        {
            string match_id = match.MatchId.ToString();
            if (all_matchings == null)
                all_matchings = new Dictionary<string, MatchData>();

            if (match == null)
                return false;

            if (all_matchings.ContainsKey(match_id))//all_matching already has this match_id
            {
                all_matchings[match_id] = match;
                return true;
            }

            all_matchings.Add(match_id, match);
            return true;
        }

        public bool RemoveMatching(MatchData match)
        {
            string match_id = match.MatchId.ToString();

            if (all_matchings == null)
                return true;

            if (match == null)
                return false;

            if (all_matchings.ContainsKey(match_id))
               all_matchings.Remove(match_id);

            return true;
        }

        public void RemoveMatching(string MatchId)
        {
            if (all_matchings != null && all_matchings.ContainsKey(MatchId))
                all_matchings.Remove(MatchId);
        }

        public MatchData GetMatchingData(int _match_id)
        {
            string match_id=_match_id.ToString();
            if (
                all_matchings != null &&
                all_matchings.ContainsKey(match_id)
                )
                return all_matchings[match_id];
            return null;

        }
        public MatchData GetMatchingData(string _match_id)
        {
            try
            {
                int match_id = int.Parse(_match_id);
                return GetMatchingData(_match_id);
            }
            catch { return null; }

        }

    }

}
