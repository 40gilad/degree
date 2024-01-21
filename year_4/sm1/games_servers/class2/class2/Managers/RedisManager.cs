﻿using StackExchange.Redis;

namespace class2.Managers
{
    public class RedisManager
    {
        private static string endPoint = "redis-10284.c323.us-east-1-2.ec2.cloud.redislabs.com";
        private static string password = "1D1HPjD3J7cbRn8Lr1U6cQ3Apa9DY8EO";
        private static int port = 10284;

        private static Lazy<ConnectionMultiplexer> lazyConnectionMultiplexer;
        static RedisManager()
        {
            RedisManager.lazyConnectionMultiplexer = new Lazy<ConnectionMultiplexer>(() =>
            {
                var configurationOptions = new ConfigurationOptions
                {
                    AbortOnConnectFail = false,
                    EndPoints = { { endPoint, port } }
                    ,
                    Password = password
                    ,
                    ConnectTimeout = 10000
                };
                return ConnectionMultiplexer.Connect(configurationOptions);
            });
        }

        public static ConnectionMultiplexer connection
        {
            get
            {
                return lazyConnectionMultiplexer.Value;
            }
        }
    }
}