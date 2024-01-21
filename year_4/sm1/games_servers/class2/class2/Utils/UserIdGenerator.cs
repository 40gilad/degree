using System.Text;
using System.Text;
namespace class2.Utils
{
    public class UserIdGenerator
    {

        public static string ToId(string emailAddress)
        {
            StringBuilder userIdBuilder = new StringBuilder();

            foreach (char character in emailAddress)
            {
                int asciiValue = (int)character;
                userIdBuilder.Append(asciiValue);
            }

            return userIdBuilder.ToString();
        }
    }
}
