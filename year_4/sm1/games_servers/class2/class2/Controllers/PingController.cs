using class2.Utils;
using Microsoft.AspNetCore.Mvc;

namespace class2.Controllers
{
    [Route("api/")]
    [ApiController]
    public class PingController : Controller
    {
        [HttpGet("PingCheck")]
        public string PingCheck()
        {
            PrintService.Print(txt : "Ping request to server", get : true); ;
            return "Pong";
        }

        [HttpPost("PingCheck")]
        
        public Dictionary<string,object> PingCheck([FromBody] Dictionary<string,object> data)
        {
            PrintService.Print(txt:"Ping request to server",post: true);
            data.Add("Response{     ", "Pingcheck");
            data.Add("Pong", DateTime.UtcNow.ToString()+ "      }");
            return data;
        }

    }
}
