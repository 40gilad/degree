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
            ret.Add("Response: ", "GetUser " + Email);
            PrintService.Print(txt: "GetEmployee with id " + Email, get: true);
            User user = UserManager.Instance.GetUser(UserIdGenerator.ToId(Email));

            if (user != null)
            {
                ret.Add("Message", "Success");
                ret.Add("Email", user.email);
                ret.Add("Password", user.password);
                PrintService.Print(txt: "Returns User " + user.email);
            }
            else
            {
                ret.Add("Message", "User " + Email + " not exist");
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
        /*
        #region Put Employee
        [HttpPut("PutEmployee")]
        public Dictionary<string, object> PutEmployee([FromBody] Dictionary<string, object> data)
        {
            Dictionary<string, object> ret = new Dictionary<string, object>();
            ret.Add("Response: ", "PutEmployee");
            try
            {
                PrintService.Print(txt: "PutEmployee", put: true);
                if (data.ContainsKey("Id") && data.ContainsKey("Name"))
                {
                    int emp_id = int.Parse(data["Id"].ToString());
                    string new_emp_name = data["Name"].ToString();
                    Employee curr = new Employee(emp_id, new_emp_name);
                    if (EmployeeManager.Instance.UpdateEmployee(curr))
                    {
                        PrintService.Print(txt: "Employee " + emp_id + " Updated name: " + new_emp_name);
                        ret.Add("Message", "Employee " + emp_id + " Updated name: " + new_emp_name);
                    }
                    else
                    {
                        ret.Add("Message", "Employee " + emp_id + " is null or not exist");
                        PrintService.Print(txt: "Returned error: Emplyoee" + emp_id + " is null or not exist ");
                    }

                }
            }
            catch (Exception e)
            {
                ret.Add("Exception Message", e);
            }
            return ret;
        }

        #endregion

        #region Delete Employee
        [HttpDelete("DeleteEmployee/{id}")]
        public Dictionary<string, object> DeleteEmployee(int id)
        {
            Dictionary<string, object> ret = new Dictionary<string, object>();
            ret.Add("Response: ", "DeleteEmployee");

            PrintService.Print(txt: "DeleteEmployee", delete: true);
            if (EmployeeManager.Instance.DeleteEmployee(id))
            {
                PrintService.Print(txt: "Employee " + id + " Removed");
                ret.Add("Message", "Employee " + id + " Removed");
            }
            else
            {
                ret.Add("Message", "Employee " + id + "<0, null or not exist");
                PrintService.Print(txt: "Returned error: Emplyoee" + id + "<0, null or not exist ");
            }
            return ret;
        }
        #endregion

        */

    }
}
