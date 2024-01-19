using class2.Models;
namespace class2.Managers
{
    public class EmployeeManager
    {
        private Dictionary<int, Employee> emp_data;

        #region Singleton
        public static EmployeeManager _instance;
        public static EmployeeManager Instance
        {
            get
            {
                if (_instance == null)
                    _instance = new EmployeeManager();
                return _instance;
            }
        }
        #endregion
        public EmployeeManager()
        {
            emp_data = new Dictionary<int, Employee>();
        }

        public Employee GetEmployee(int id)
        {
            if (
                id < 0
                || !emp_data.ContainsKey(id)
                || emp_data == null
                )
                return null; // if emp_data is null, dont create one because it's get and not post
            return emp_data[id];
        }

        public bool AddEmployee(Employee emp)
        {
            if (emp_data == null)
                emp_data = new Dictionary<int, Employee>();
            if (emp == null)
                return false;
            if (!emp_data.ContainsKey(emp.id))
            {
                emp_data.Add(emp.id, emp);
                return true;
            }
            else return false;
        }

        public bool UpdateEmployee(Employee emp)
        {
            if (
                emp_data == null
                || emp == null
                || !emp_data.ContainsKey(emp.id)
                )
                return false;
            emp_data[emp.id] = emp;
            return true;
        }

        public bool DeleteEmployee(int id)
        {
            if (
                emp_data == null
                || id <0
                || !emp_data.ContainsKey(id)
                )
                return false;
            emp_data.Remove(id);
            return true;
        }
    }
}
