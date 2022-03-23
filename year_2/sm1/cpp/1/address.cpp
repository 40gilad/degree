#include "address.h"
#include "copystr.h"
using namespace std;

/******************************** CONSTRUCTORS ***********************/

address::address() //default
    : street(new char[1]), city(new char[1]), postalcode(0)
{
    cout << "Address DEFAULT CUNSTRUCTOR done successfully with the following values: " << endl;
    street[0] = '\0';
    city[0] = '\0';
    postalcode = 0;
    this->printAD();
}

address::address(const address &add) //copy
    : street(copystring(add.street)), city(copystring(add.city)), postalcode(add.postalcode)
{
    cout << "Address COPY CUNSTRUCTOR done successfully with the following values: " << endl;
    this->printAD();
}

address::address(const char *stret, const char *citi, int postal) //parameter constructor
    : street(new char[1]), city(new char[1]), postalcode(0)
{
    street[0] = '\0';
    city[0] = '\0';
    cout << "Address PARAMETER CUNSTRUCTOR done successfully with the following values: " << endl;
    setstreet(stret);
    setcity(citi);
    setpostalcode(postal);
    this->printAD();
}

/******************************** DESTRUCTORS ************************/
address::~address()
{
    return;
    delete[] this->street;
    delete[] this->city;
}
/******************************* SETTERS *******************************/

void address::setstreet(const char *stret)
{
    if (stret == nullptr)
    {
        cout << "ERROR!       No street name found" << endl;
        return;
    }
    delete[] this->street;
    this->street = copystring(stret);
    if (this->street == nullptr)
    {
        cout << "fail allocate memory" << endl;
        exit(1);
    }
}
void address::setcity(const char *citi)
{
    if (citi == nullptr)
    {
        cout << "ERROR!       No city name found" << endl;
        return;
    }
    delete[] this->city;
    this->city = copystring(citi);
    if (this->city == nullptr)
    {
        cout << "fail allocate memory" << endl;
        exit(1);
    }
}
void address::setpostalcode(int postal)
{
    postalcode = postal;
}

/********************************** GETTERS *******************/
const char *address::getstreet()
{
    return street;
}

const char *address::getcity()
{
    return city;
}

int address::getpostal()
{
    return postalcode;
}

/****************************** OTHER METHODS *************************/

void address::printAD()
{
    cout << "street: " << getstreet() << endl;
    cout << "city: " << getcity() << endl;
    cout << "postal code: " << getpostal() << endl;
}

address *address::operator=(const address &a)
{
    this->city = new char[1];
    this->street = new char[1];
    this->postalcode = a.postalcode;
    this->city = copystring(a.city);
    this->street = copystring(a.street);
    return this;
}