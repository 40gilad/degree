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
            // running on the sorted list. additional for (with j=i+1) to find the next player that they are
            // ptobably match. when match has found, check if match is valid and rating gap is ok.
            // if so, removes matched players from SearchingManager list, sends both the matching data
            // and update their session and their user state to preplay.


            bool is_found_match = false;
            List<SearchingData> sorted_searching_list = SearchingManager.Instance.GetSearchingList().
                OrderBy(value => value.PlayerRating).ToList();

            if (sorted_searching_list != null )
            {//if sorted_searching_list not null and it has more that 1 playes -> can match them

                for (int i = 0;
                    i < sorted_searching_list.Count && sorted_searching_list.Count > 1;
                    i++, is_found_match=false
                    )
                { 
                    SearchingData first_user = sorted_searching_list[i];

                    for (int j = i + 1;
                        j < sorted_searching_list.Count && !is_found_match;
                        j++
                        )
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

                                foreach (User user in matched_users)
                                {
                                    //send data to matched players, change their state,
                                    //remove from SearchingManager annd update session

                                    user.SendMessage(json_data);
                                    user.CurrState = User.UserState.PrePlay;
                                    SearchingManager.Instance.RemoveFromSearchingList(user.UserId);
                                    SessionsManager.Instance.UpdateUser(user);
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
                                is_found_match = true;

                                //remove users from sorted_list (iterated list)
                                sorted_searching_list.Remove(first_user);
                                sorted_searching_list.Remove(second_user);
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
