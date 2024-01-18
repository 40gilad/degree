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
                if(_instance == null)
                    _instance = new EmployeeManager();
                return _instance;
            }
        }
        #endregion
        public EmployeeManager()
        {
            emp_data = new Dictionary<int,Employee>();
        }

        public bool AddEmployee(Employee emp)
        {
            if (emp_data==null)
                emp_data = new Dictionary<int, Employee>();
            if (emp == null) 
                return false;
            if (!emp_data.ContainsKey(emp.id))
            {
                emp_data.Add(emp_data.Id,)
                return true;
            }
            else return false;
        }
    }

}
