using GameServer_ex2.Managers;
using GameServer_ex2.Models;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace GameServer_ex2.Threads
{
    internal class MatchingThread
    {
        private Thread curr_thread;
        private bool is_mathing_run = false;
        private int gap_to_match = 50;
        private int match_id;
        public MatchingThread()
        {
        }

        public bool StartThread()
        {
            match_id = 0;
            is_mathing_run = true;
            curr_thread = new Thread(new ThreadStart(RunMatching));
            curr_thread.Start();
            return true;
        }

        public bool StartThread(string uid)
        {
            is_mathing_run = true;
            //curr_thread = new Thread(new ThreadStart(RunMatching));
            return true;
        }

        public void RunMatching()
        {
            while (is_mathing_run)
            {
                Console.WriteLine("\nthread run "+DateTime.UtcNow);
                MatchPlayers();
                Thread.Sleep(1000); // wait 1000 miliseconds= 1 second
            }
        }

        private void MatchPlayers()
        {
            bool is_found_match = false;
            List<SearchingData> sorted_searching_list = SearchingManager.Instance.GetSearchingList().
                OrderBy(value => value.PlayerRating).ToList();

            if (sorted_searching_list != null && sorted_searching_list.Count > 1)
            {//if sorted_searching_list not null and it has more that 1 playes -> can match them
                for (int i = 0;
                    i < sorted_searching_list.Count;
                    i++)
                {
                    SearchingData first_user = sorted_searching_list[i];
                    for (int j = i + 1;
                        j < sorted_searching_list.Count && !is_found_match;
                        j++)
                    {
                        SearchingData second_user = sorted_searching_list[j];
                        if (AreMatching(first_rating: first_user.PlayerRating, second_rating: second_user.PlayerRating))
                        {//users i,j has matching rating
                            List<User> matched_users = new List<User>()
                            {
                                SessionsManager.Instance.UserSession[first_user.UserID],
                                SessionsManager.Instance.UserSession[second_user.UserID]

                            };
                            if(CheckUsersValidity(matched_users))
                            {//both users are valid to match
                                Dictionary<string, object> data = new Dictionary<string, object>()
                                {
                                    {"Service","ReadyToPlay" },
                                    {"TempMatchId",match_id }
                                };
                                string json_data = JsonConvert.SerializeObject(data);

                                foreach (User user in matched_users)//send data to matched players
                                {
                                    user.SendMessage(json_data);
                                    user.CurrState = User.UserState.PrePlay;
                                    SearchingManager.Instance.RemoveFromSearchingList(user.UserId);
                                }

                                List<SearchingData> temp_search_data = new List<SearchingData>()
                                {//when "Ready" from client will arrive, it will be changed in this list
                                    first_user,
                                    second_user
                                };

                                MatchData curr_match_data = new MatchData(
                                    search_data: temp_search_data, curr_match_id: match_id
                                    );

                                MatchingManager.Instance.AddMatching(curr_match_data);

                            }
                        }

                    }

                }
            }
        }

        private bool AreMatching(int first_rating, int second_rating)
        { //check if players rating gap is not more than detrmined gap
            int curr_gap = Math.Abs(first_rating - second_rating);//gap between players rating

            if (curr_gap <= gap_to_match)
                return true;
            return false;
        }

        private bool CheckUsersValidity(List<User> users)
        { //check if both players are valid
            foreach (User user in users)
            {
                if (IsValidUser(user))
                    return true;
            }
            return false;
        }
        private bool IsValidUser(User user)
        { // check if player not null, in matching state and websocket is connected
            if (user != null &&
                user.CurrState == User.UserState.Matching &&
                user.IsUserLiveWithSession())
                return true;
            return false;
        }

        public void StopThread()
        {
            is_mathing_run = false;
        }
    }
}
