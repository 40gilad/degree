using class2.Managers;
using class2.Models;
using class2.Services;
using class2.Utils;
using Microsoft.AspNetCore.Mvc;

namespace class2.Controllers
{
    [Route("api/")]
    [ApiController]
    public class UserController : Controller
    {
        #region Get User
        [HttpGet("Login/{Email}&{Password}")]
        public Dictionary<string, object> GetUser(string Email, string password)
        {
            Dictionary<string, object> ret = new Dictionary<string, object>();
            PrintService.Print(txt: "GetEmployee with id " + Email, get: true);
            User user = UserManager.Instance.GetUser(UserIdGenerator.ToId(Email));

            if (user != null)
            {
                ret.Add("IsLoggedIn", "true");
                ret.Add("UserId", UserIdGenerator.ToId(user.email));
                ret.Add("Response", "Login");
                PrintService.Print(txt: "Returns User " + user.email);
            }
            else
            {
                ret.Add("Message", "User " + Email + " not exist");
                ret.Add("Response", "Login");
                ret.Add("IsLoggedIn", "false");
                PrintService.Print(txt: "Returned error: User"+ Email +" not exist ");
            }
            return ret;
        }

        #endregion
        
        #region Post User
        [HttpPost("Register")]
        public Dictionary<string, object> PostEmployee([FromBody] Dictionary<string, object> data)
        {
            Dictionary<string, object> ret = new Dictionary<string, object>();
            ret.Add("Response: ", "Regiser");
            PrintService.Print(txt: "UserRegiser", post: true);

            if (data.ContainsKey("Email") && data.ContainsKey("Password"))
            {
                string u_mail = data["Email"].ToString();
                string u_password = data["Password"].ToString();
                string u_id= UserIdGenerator.ToId(u_mail);
                User curr = new User(u_id,u_mail, u_password);

                if (UserManager.Instance.AddUser(curr))
                {
                    PrintService.Print(txt: "User " + data["Email"] + " Added to UserManeger");
                    ret.Add("Message", "User " + data["Email"] + " Added to UserManeger");
                }
                else
                {
                    ret.Add("Message", " User is null or already in the system");
                    PrintService.Print(txt: "User " + data["Email"] + ", " + " is null or already in the system");
                }

            }
            return ret;
        }


        #endregion

    }
}
