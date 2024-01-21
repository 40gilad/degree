using class2.Managers;
using class2.Utils;
using StackExchange.Redis;

namespace class2.Services
{
    public class RedisService
    {
        #region get/set Strings

        private static void RedisSet(string key,string val)
        {
            var DBconnection = RedisManager.connection.GetDatabase();
            try
            {
                DBconnection.StringSet(key, val);
            }
            catch(Exception e) {
                string m =e.Message;
                PrintService.Print(e.Message);
            }
            PrintService.Print("Reddis Added");
        }

        private static string RedisGet(string key)
        {
            var DBconnection = RedisManager.connection.GetDatabase();
            return DBconnection.StringGet(key);
        }


        #endregion

        #region get/set Dictionary

        private static Dictionary<string, string> RedisGetDictionary(string _Key)
        {
            Dictionary<string, string> _ret = new Dictionary<string, string>();
            try
            {
                var _cacheConnection = RedisManager.connection.GetDatabase();
                HashEntry[] _data = _cacheConnection.HashGetAll(_Key);
                foreach (HashEntry hash in _data)
                    _ret.Add(hash.Name, hash.Value);
            }
            catch (Exception e)
            { }
            return _ret;
        }

        private static void RedisSetDictionary(string _Key, Dictionary<string, string> _UserDetails)
        {
            try
            {
                var _cacheConnection = RedisManager.connection.GetDatabase();
                HashEntry[] _entry = new HashEntry[_UserDetails.Count];

                int _count = 0;
                foreach (string s in _UserDetails.Keys)
                {
                    RedisKey _key = new RedisKey(s);
                    RedisValue _name = new RedisValue(s);
                    RedisValue _value = new RedisValue(_UserDetails[s]);
                    _entry[_count++] = new HashEntry(_name, _value);

                }
                _cacheConnection.HashSet(_Key, _entry);
            }
            catch (Exception e) { }
        }

        #endregion

        #region Remove Keys

        private static bool RemoveData(string key)
        {
            var DBconnection = RedisManager.connection.GetDatabase();
            return DBconnection.KeyDelete(key);
        }

        #endregion

        #region Employee

        public static void SetEmployeeDetails(string key, Dictionary<string,string> emp_dict)
        {
            RedisSetDictionary(key+"#EDetailes", emp_dict);
        }

        public static Dictionary<string, string> GetEmployeeDetails(string key)
        {
            return RedisGetDictionary(key+"#EDetailes");
        }

        public static bool DeleteEmployeeDetails(string key)
        {
            return RemoveData(key+ "#EDetailes");
        }
        #endregion

        #region User
        public static void SetUserDetails(string key, Dictionary<string, string> emp_dict)
        {
            RedisSetDictionary(key + "#UDetailes", emp_dict);
        }

        public static Dictionary<string, string> GetUserDetails(string key)
        {
            return RedisGetDictionary(key + "#UDetailes");
        }

        public static bool DeleteUserDetails(string key)
        {
            return RemoveData(key + "#UDetailes");
        }
        #endregion
    }
}
