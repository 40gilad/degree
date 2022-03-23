#include "job.h"
#include "copystr.h"
using namespace std;

/***************************** CONSTRUCTORS ********************/

job::job() //default constructor
    : title(new char[1]), salary(0), department(departmentenum::unemployeed)
{
    title[0] = '\0';
    cout << "Job DEFAULT CUNSTRUCTOR done successfully with the following values: " << endl;
    this->printJ();
}

job::job(const job &Job) //copy constructor
    : title(copystring(Job.title)), salary(Job.salary), department(Job.department)
{
    cout << "Job COPY CONSTRUCTOR done successfully with the following values: " << endl;
    this->printJ();
}

job::job(const char *titl, const int salar, departmentenum dep) //parameter constructor
    : title(new char[1]), salary(0), department(departmentenum::unemployeed)
{
    cout << "Job PARAMETER CONSTRUCTOR done succefully with the following values: " << endl;
    title[0] = '\0';
    settitle(titl);
    setsalary(salar);
    setdepartment(dep);
    this->printJ();
}

/************************* DESTRUCTOS *********************/
job::~job()
{
    delete[] this->title;
}
void job::settitle(const char *titl)
{
    if (titl == nullptr)
    {
        cout << "ERROR!       No phone number found" << endl;
        return;
    }
    delete[] this->title;
    this->title = copystring(titl);
    if (this->title == nullptr)
    {
        cout << "fail allocate memory" << endl;
        exit(1);
    }
}

/********************************* SETTERS *********************************/

void job::setdepartment(departmentenum dep)
{
    department = dep;
}

void job::setsalary(int salar)
{
    salary = salar;
}

/********************************** GETTERS ************************/

const char *job::gettitle()
{
    return title;
}

int job::getsalary()
{
    return salary;
}

departmentenum job::getdepartment()
{
    return department;
}

int job::work()
{
    return getsalary();
}

/******************************** OTHER METHODS **********************/

void job::printJ()
{
    cout << "title: " << gettitle() << endl;
    cout << "salary: " << getsalary() << endl;
    cout << "Department: ";
    switch (int(department))
    {
    case 0:
        cout << "Prodeuct" << endl;
        break;
    case 1:
        cout << "Sales" << endl;
        break;
    case 2:
        cout << "Marketing" << endl;
        break;
    case 3:
        cout << "Art" << endl;
        break;
    case 4:
        cout << "Unemployeed" << endl;
        break;
    default:
        cout << "Not found" << endl;
        break;
    }
}

void job::retire()
{
    title = nullptr;
    salary = 0;
    department = departmentenum::unemployeed;
}

job *job::operator=(const job &j)
{
    this->title = new char[1];
    switch (int(j.department))
    {
    case 0:
        this->department = departmentenum::pruduct;
        break;
    case 1:
        this->department = departmentenum::sales;
        break;
    case 2:
        this->department = departmentenum::marketing;
        break;
    case 3:
        this->department = departmentenum::art;
        break;
    case 4:
        this->department = departmentenum::unemployeed;
        break;
    default:
        this->department= departmentenum::unemployeed;
        break;
    }
    this->salary = j.salary;
    this->title = copystring(j.title);
    return this;
}