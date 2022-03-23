#include <iostream>
#ifndef ADDRESS_H_
#define ADDRESS_H_
using namespace std;

class address
{
private:
    char *street;
    char *city;
    int postalcode;

public:
    address* operator=(const address &a);
    address();                                                //default constructor
    address(const address &ad);                               //copy constructor
    address(const char *stret, const char *citi, int postal); //parameter constructor
    ~address();
    void setstreet(const char *stret);
    void setcity(const char *citi);
    void setpostalcode(int postal);
    const char *getstreet();
    const char *getcity();
    int getpostal();
    void printAD();
};
#endif