namespace class2.Models
{
    public class Employee
    {
        private int _id;
        private string _name;
        public int id { get { return _id; } }
        public string name { get { return _name; } }

        public Employee(int id, string name)
        {
            _id = id;
            _name = name;
        }
    }
}
