using class2.Utils;
using Microsoft.AspNetCore.Mvc;

namespace class2.Controllers
{
    [Route("api/")]
    [ApiController]
    public class EmployeeController : Controller
    {
        [HttpGet("GetEmployee/{id}")]
        public Dictionary<string, object> GetEmployee(int id)
        {
            Dictionary<string,object> emp = new Dictionary<string,object>();
            PrintService.Print(txt: "GetEmp with id " + id +" ", get: true); ;
            emp.Add("Response ", "GetEmp " + id);
            return emp;
        }

        [HttpPost("PostEmployee")]

        public Dictionary<string, object> PostEmployee([FromBody] Dictionary<string, object> data)
        {
            Dictionary<string, object> emp = new Dictionary<string, object>();
            PrintService.Print(txt: "PostEmp with id=" + data["id"] +"| name=" + data["name"] +" ", put: true); ;
            data.Add("Response ", "PostEmployee");
            return emp;
        }


        /*
        [HttpPut("PutEmployee")]

        
        public Dictionary<string, object> PutEmployee([FromBody] Dictionary<string, object> data)
        {
            PrintService.Print(txt: "GetEmp with id " + id + " ", get: true); ;

            return data;
        }

        [HttpDelete("DeleteEmployee")]

        public Dictionary<string, object> DeleteEmployee([FromBody] Dictionary<string, object> data)
        {

            return data;
        }
        */

    }
}
