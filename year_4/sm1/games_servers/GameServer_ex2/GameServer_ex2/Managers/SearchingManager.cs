using GameServer_ex2.Models;
using GameServer_ex2.Threads;
using System.Collections.Generic;

namespace GameServer_ex2.Managers
{
    internal class SearchingManager
    {
        private Dictionary<string, int> searching_dict;
        private MatchingThread curr_matching_thread;

        #region Singleton
        private static SearchingManager instance;
        public static SearchingManager Instance
        {
            get
            {
                if (instance == null)
                    instance = new SearchingManager();
                return instance;
            }
        }
        #endregion

        SearchingManager()
        {
            searching_dict = new Dictionary<string, int>();
            curr_matching_thread = new MatchingThread();
            curr_matching_thread.StartThread();
        }

        public bool AddToSearchingDict(string uid,int rating)
        {
            if (searching_dict == null)
                searching_dict = new Dictionary<string, int>();
            if (uid == null)
                return false;
            if (searching_dict.ContainsKey(uid))
            {
                searching_dict[uid] = rating;
                return true;
            }
            searching_dict.Add(uid,rating);
            return true;
        }

        public bool RemoveFromSearchingList(string uid)
        {
            if (searching_dict == null)
                searching_dict = new Dictionary<string, int>();
            if (uid==null)
                return false;
            if (searching_dict.ContainsKey(uid))
            {
                searching_dict.Remove(uid);
                return true;
            }
            else
                return false;

        }

        public List<SearchingData> GetSearchingList()
        {
            List<SearchingData> searching_data=new List<SearchingData>();
            foreach(string uid in searching_dict.Keys)
            {
                searching_data.Add
                    (new SearchingData(
                        _uid: uid,
                        rating: searching_dict[uid]
                        )
                    );
            }
            return searching_data;
        }
    }
}
