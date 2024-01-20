using class2.Models;
using class2.Services;
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
            Dictionary<string, string> res_emp = null;
            if (id  > 0)
                res_emp = RedisService.GetEmployeeDetails(id.ToString());
            else
                return null;

            if (res_emp!=null && res_emp.Count<=0)
                return null;

            if (res_emp!=null)
                return Employee.ToEmployee(res_emp);
            return null;
        }

        public bool AddEmployee(Employee emp)
        {
            string emp_id = emp.id.ToString();
            if (emp == null)
                return false;

            Dictionary<string, string> temp_emp = RedisService.GetEmployeeDetails(emp_id);
            if (temp_emp.Count == 0) // Uid not exist
            {
                RedisService.SetEmployeeDetails(emp_id, emp.ToDict());
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
