using class2.Utils;

namespace class2.Models
{
    public class User
    {
        private string _id;
        private string _mail;
        private string _password;
        private int _money;
        private int _xp;
        private int _level;
        public string id { get { return _id; } }
        public string email { get { return _mail; } }
        public string password { get { return _password; } }
        public int money { get { return _money; } set { _money = value; } }
        public int xp { get { return _xp; } set { _xp = value; } }
        public int level { get { return _level; } set { _level = value; } }


        public User(string id, string mail,string password, int money=0, int xp =0, int level = 1)
        {
            _id = id;
            _mail = mail;
            _password = password;
            _money = money;
            _xp = xp;
            _level = level;
        }

        public static User ToUser(Dictionary<string, string> user_dict)
        {
            try
            {
                string id= String.Empty,password=String.Empty;
                int money = -1, xp = -1, level = -1;
                string mail = string.Empty;

                if (user_dict.ContainsKey("Id") && user_dict.ContainsKey("Mail"))
                {
                    id = user_dict["Id"];
                    mail = user_dict["Mail"];
                    password = user_dict["Password"];
                    money = int.Parse(user_dict["Money"]);
                    xp = int.Parse(user_dict["XP"]);
                    level = int.Parse(user_dict["Level"]);
                }

                if (id != String.Empty && mail != string.Empty)
                    return new User(id, mail,password, money, xp, level);

            }
            catch (Exception e) { PrintService.Print("User.cs Exceotion: " + e.Message); }
            return null;
        }

        public Dictionary<string, string> ToDict()
        {
            return new Dictionary<string, string>()
            {
                {
                    "Id", _id
                },
                {
                    "Mail", _mail
                },
                                {
                    "Password", _password
                },
                {
                    "Money", _money.ToString()
                },
                {
                    "XP", _xp.ToString()
                },
                {
                    "Level", _level.ToString()
                }
            };
        }
    }
}
