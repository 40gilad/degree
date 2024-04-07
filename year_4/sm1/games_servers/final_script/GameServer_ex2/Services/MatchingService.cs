﻿using GameServer_ex2.Models;
using GameServer_ex2.Services;
using GameServer_ex2.Managers;
using GameServer_ex2.Models;
using GameServer_ex2.Threads;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GameServer_ex2.Services
{
    public class MatchingService
    {
        public static Dictionary<string, object> Create(MatchData CurMatchData)
        {
            return new Dictionary<string, object>()
            {
                { "Service","StartMatch"},
                { "MatchId",CreateRoom(CurMatchData)}
            };
        }

        private static string CreateRoom(MatchData CurMatchData)
        {
            int dbMatchId = 1;
            string redisMatchId = RedisService.GetMatchId();
            if (redisMatchId != null && redisMatchId != string.Empty)
                dbMatchId = int.Parse(redisMatchId) + 1;

            RedisService.SetMatchId(dbMatchId.ToString());

            GameThread gameroom = new GameThread(dbMatchId.ToString(), CurMatchData);
            RoomsManager.Instance.AddRoom(dbMatchId.ToString(), gameroom);
            gameroom.StartGame();

            return dbMatchId.ToString();
        }
    }
}
