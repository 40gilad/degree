using GameServer_ex2.Managers;
using GameServer_ex2.Models;
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
        public MatchingThread()
        {
        }

        public bool StartThread()
        {
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
                Console.WriteLine("\nthread run ");
                MatchPlayers();
                Thread.Sleep(1000); // wait 1000 miliseconds= 1 second
            }
        }

        private void MatchPlayers()
        {
            bool is_found_match = false;
            List<SearchingData> sorted_searching_list = SearchingManager.Instance.GetSearchingList().
                OrderBy(value => value.PlayerRating).ToList();

            if (sorted_searching_list != null && sorted_searching_list.Count > 0)
            {
                for (int i = 0;
                    i < sorted_searching_list.Count;
                    i++)
                {
                    SearchingData first = sorted_searching_list[i];
                    for (int j = i + 1;
                        j < sorted_searching_list.Count && !is_found_match;
                        j++)
                    {
                        SearchingData second = sorted_searching_list[j];
                        if (AreMatching(first_rating: first.PlayerRating, second_rating: second.PlayerRating))
                        {
                            List<User> matched_users = new List<User>()
                            {
                                SessionsManager.Instance.UserSession[first.UserID],
                                SessionsManager.Instance.UserSession[second.UserID]

                            };
                            bool is_valid_users=CheckUsersValidity(matched_users);
                        }

                    }

                }
            }
        }

        private bool AreMatching(int first_rating, int second_rating)
        {
            int curr_gap = Math.Abs(first_rating - second_rating);//gap between players rating

            if (curr_gap <= gap_to_match)
                return true;
            return false;
        }

        private bool CheckUsersValidity(List<User> users)
        {
            foreach (User user in users)
            {
                if (!IsValidUser(user))
                    return true;
            }
            return false;
        }
        private bool IsValidUser(User user)
        {
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
