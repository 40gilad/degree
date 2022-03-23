#include "person.h"
#include "address.h"
#include "Job.h"
#include "copystr.h"
using namespace std;

/******************** CONSTRUCTORS *******************/

person::person()
    : name(new char[1]), phoneNumber(new char[1]), email(new char[1]), savings(0), add(), jb()
{
    if (this == nullptr)
    {
        cout << "ERROR! constructing nullptr!" << endl;
        exit(1);
    }
    cout << "Person DEFAULT CONSTRUCTOR done successfully with the following values: " << endl;
    name[0] = '\0';
    phoneNumber[0] = '\0';
    email[0] = '\0';
    printP();
}

person::person(const char *nam, const char *phonenumber, const char *mail, const address &ad, const job &Job) //parameter
    : name(new char[1]), phoneNumber(new char[1]), email(new char[1]), savings(0), add(ad), jb(Job)
{
    cout << "Person PARAMETER CONSTRUCTOR done successfully with the following values: " << endl;
    name[0] = '\0';
    phoneNumber[0] = '\0';
    email[0] = '\0';
    setname(nam);
    setphonenum(phonenumber);
    setemail(mail);
    this->printP();
}

person::person(const person &p) //copy
    : name(copystring(p.name)), phoneNumber(copystring(p.phoneNumber)), email(copystring(p.email)), jb(p.jb), add(p.add)
{
    cout << "Person COPY CONSTRUCTOR done successfully with the following values: " << endl;
    this->printP();
}

/****************************** DESTRUCTORS ***************************/

person::~person()
{
    delete[] this->name;
    delete[] this->phoneNumber;
    delete[] this->email;
    jb.~job();
    add.~address();
}

/************************* SETTERS ************************/

void person::setname(const char *nam)
{
    if (nam == nullptr)
    {
        cout << "ERROR!       No name found" << endl;
        return;
    }
    delete[] this->name;
    name = copystring(nam);
    if (this->name == nullptr)
    {
        cout << "fail allocate memory" << endl;
        exit(1);
    }
}

void person::setphonenum(const char *phone)
{
    if (phone == nullptr)
    {
        cout << "ERROR!       No phone number found" << endl;
        return;
    }
    delete[] this->phoneNumber;
    this->phoneNumber = copystring(phone);
    if (this->phoneNumber == nullptr)
    {
        cout << "fail allocate memory" << endl;
        exit(1);
    }
}

void person::setemail(const char *mail)
{
    if (mail == nullptr)
    {
        cout << "ERROR!       No mail address found" << endl;
        return;
    }
    delete[] this->email;
    this->email = copystring(mail);
    if (this->email == nullptr)
    {
        cout << "fail allocate memory" << endl;
        exit(1);
    }
}

/************************************* GETTERS ***************************/

const char *person::getname()
{
    return this->name;
}

const char *person::getphonenum()
{
    return phoneNumber;
}

const char *person::getemail()
{
    return email;
}

int person::getsaving()
{
    return savings + jb.getsalary();
}

/**************************** OTHER METHODS ************************************/

person *person::operator=(const person &p)
{
    this->name = new char[1];
    this->phoneNumber = new char[1];
    this->email = new char[1];
    this->savings = p.savings;
    this->add = p.add;

    this->jb = p.jb;
    this->name = copystring(p.name);
    this->phoneNumber = copystring(p.phoneNumber);
    this->email = copystring(p.email);
    return this;
}

int person::orderfood(address ad, int amount)
{
    cout << endl;
    if (getsaving() > amount)
    {
        savings = getsaving() - amount;
        cout << getname() << ", Your Food is on its way, enjoy your meal!" << endl;
        return 1;
    }
    cout << getname() << ", You don't have enough money to order food! " << endl;
    return 0;
}

int person::work()
{
    return jb.work();
}

void person::retire()
{
    jb.retire();
}

void person::printP()
{
    if (this == nullptr)
    {
        cout << endl
             << "ERROR! this person is nullptr. nothing to print" << endl;
        return;
    }
    cout << endl;
    cout << "name: " << getname() << endl;
    cout << "phone number : " << getphonenum() << endl;
    cout << "email: " << getemail() << endl;
    cout << "savings: " << getsaving() << endl;
    add.printAD();
    jb.printJ();
    cout << endl;
}