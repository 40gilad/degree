#include <iostream>
#ifndef FRAC_H
#define FRAC_H
using namespace std;
class fraction
{
private:
    int num;
    int den;
    void normal();

public:
    fraction();
    fraction(const fraction &f);
    fraction(int up, int down);
    fraction(int x);
    fraction(float x);
    ~fraction();
    int getNum();
    int getDen();
    void print(); // TEMPORARY METHOD!!!!!
    fraction *operator=(const fraction &f);
    int operator<(fraction f);

    /***************** OPERATORS METHODS *********************/

    fraction &operator+(int x);
    fraction &operator-(int x);
    void operator+=(int x);
    void operator+=(fraction &f);
    void operator-=(int x);
    void operator-=(fraction &f);
    fraction &operator++();
    fraction &operator--();
    fraction &operator++(int x);
    fraction &operator--(int x);
    int operator==(fraction f);
    fraction &operator!();
    operator int()const;
    operator float()const;
};

/*************************** FUNCTIONS *******************************/
fraction operator+(fraction &first, fraction &sec);
fraction operator+(int x, fraction &f);
fraction operator-(fraction &first, fraction &sec);
fraction operator-(int x, fraction &f);
istream& operator>>(istream& input,fraction &f);
ostream& operator<<(ostream &output, fraction &f);
#endif