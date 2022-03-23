#include "managment.h"
#include "person.h"
#include <iostream>
#include <string.h>
using namespace std;

/*******************************CONSTRUCTORS**********************************/

managment::managment()
    : p_arr(new person *[SIZE]), sizeOfArr(SIZE)
{
    this->initAll();
}

managment::managment(int size)
    : p_arr(new person *[size]), sizeOfArr(size)
{
    this->initAll();
}

managment::managment (const managment &man)
:p_arr(new person * [man.sizeOfArr]),sizeOfArr(man.sizeOfArr)
{
        for (int i = 0; i < man.sizeOfArr; i++)
    {
        this->p_arr[i] = man.p_arr[i];
    }
}
/******************************* DESTRUCTORS ******************************/
managment::~managment()
{
    for (int i = 0; i < this->sizeOfArr; i++)
    {

        if (this->p_arr[i] != nullptr){
            this->p_arr[i]->~person();
            this->p_arr[i]=nullptr;
        }
    }
    delete[] this->p_arr;
}

/****************** PTIAVTE METHODS ************************/

void managment::initAll() //initilize the arrey to nullptr
{
    for (int i = 0; i < this->sizeOfArr; i++)
        this->p_arr[i] = nullptr;
}

int managment::vac() //returns the first vac place in the arrey
{
    for (int i = 0; i < this->sizeOfArr; i++)
    {
        if (this->p_arr[i] == nullptr)
            return i;
    }
    return -1;
}

void managment::incSize()
{
    person **temp;
    temp = new person *[this->sizeOfArr * 2];
    for (int i = 0; i < this->sizeOfArr; i++)
    {
        temp[i] = this->p_arr[i];
    }
    this->sizeOfArr = this->sizeOfArr * 2;
    this->p_arr = temp;
}

/***************************** PUBLIC METHODS ********************************/

void managment::setPerson(person *p)
{
    int index = -2;
    index = vac();
    while (index == -1) //index get the next index to insert person. if no space, increase the arr and gets it again
    {
        incSize();
        index = vac();
    }
    person *newP;
    newP = p;
    this->p_arr[index] = newP;
    this->p_arr[index]->printP(); //DELETEEE
}

void managment::remove(person *p)
{
    for (int i = 0; i < this->sizeOfArr; i++)
    {
        if (strcmp(this->p_arr[i]->getphonenum(), p->getphonenum()) == 0) //if strmp=0, delete person from arr
        {
            this->p_arr[i]->~person();
            this->p_arr[i] = nullptr;
            break;
        }
    }
}

void managment::printPersons()
{
    int j = 0;
    cout << endl
         << "--------------------------------------------------------------------------" << endl
         << "All persons in managment arrey:" << endl
         << endl;
    for (int i = 0; i < this->sizeOfArr; i++)
    {
        if (this->p_arr[i] != nullptr)
        {
            cout << "person number  " << ++j << ":";
            this->p_arr[i]->printP();
        }
    }
}

managment *managment::operator=(const managment &m)
{
    this->p_arr = new person* [m.sizeOfArr];
    this->sizeOfArr = m.sizeOfArr;
    for (int i = 0; i < m.sizeOfArr; i++)
    {
        this->p_arr[i] = m.p_arr[i];
    }
    return this;
}
