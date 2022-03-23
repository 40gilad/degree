#include <iostream>
#ifndef JOB_H_
#define JOB_H_
using namespace std;
enum departmentenum
{
    pruduct,
    sales,
    marketing,
    art,
    unemployeed
};
class job
{
private:
    char *title;
    int salary;
    departmentenum department;

public:
    job* operator=(const job &j);
    job();
    job(const char *titl, const int salar, departmentenum dep);
    job(const job &Job);
    ~job();
    void settitle(const char *titl);
    void setdepartment(departmentenum dep);
    void setsalary(int salar);
    const char *gettitle();
    int getsalary();
    departmentenum getdepartment();
    void printJ();
    int work();
    void retire();
};
#endif
