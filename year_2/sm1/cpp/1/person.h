
#include "job.h"
#include "address.h"
#ifndef PERSON_H_
#define PERSON_H_
using namespace std;
class person
{

public:
    person* operator=(const person &p);
    person();                                                                                              //default
    person(const person &p);                                                                               //copy
    person(const char *nam, const char *phonenumber, const char *mail, const address &ad, const job &Job); //parameter
    ~person();
    void setname(const char *nam);
    void setphonenum(const char *phone);
    void setemail(const char *mail);
    const char *getname();
    const char *getphonenum();
    const char *getemail();
    int getsaving();
    int orderfood(address ad, int amount);
    void printP();
    int work();
    void retire();

private:
    char *name;
    char *phoneNumber;
    char *email;
    int savings;
    address add;
    job jb;
};
#endif