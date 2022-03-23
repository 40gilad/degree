#include "frac.h"
#include <iostream>
using namespace std;

/********************************* CONSTRUCTORS ***********************************/

fraction::fraction() // default
    : num(0), den(1)
{
}

fraction::fraction(const fraction &f) // copy
{
    num = f.num;
    den = f.den;
    normal();
}

fraction::fraction(int x) // conversion
    : num(x * x), den(x)
{
    if (den == 0)
        den = 1;
    normal();
}

fraction::fraction(float x) // conversion
    : num(1), den(1)
{
    int before = 0, temp = 0, after = 0, counter = 0;
    before = x;
    temp = (x - before) * 1000;
    if (temp == 0)
    {
        num = before;
        return;
    }
    while (temp % 10 == 0)
    {
        ++counter;
        temp = temp / 10;
    }
    num = temp;
    if (counter == 0)
        den = 1000;
    else if (counter == 1)
        den = 100;

    else if (counter == 2)
        den = 10;
    *this += before;
}

fraction::fraction(int up, int down) // parameter
{

    if (down == 0)
    {
        cout << endl
             << "YOU CAN'T DIVIDE BY ZERO!" << endl
             << "FRACTION CONSTRUCTED WITH DEFAULT PARAMETERS: 1/1" << endl;
        num = 1;
        den = 1;
        return;
    }
    num = up;
    den = down;
    normal();
}

fraction::operator int() const
{
    return static_cast<int>(num) / static_cast<int>(den);
}

fraction::operator float() const
{
    return static_cast<float>(num) / static_cast<float>(den);
}

/********************************** DESTRUCTOR ************************************/

fraction::~fraction()
{
}
/********************************** SETTERS **************************************/

/****************************** GETTERS *****************************************/

int fraction::getNum()
{
    return num;
}

int fraction::getDen()
{
    return den;
}

/********************************** PRIVATE *************************************/

void fraction::normal()
{
    if (num == 1 || den == 1)
        return;
    int smallest = 0, root = 0;
    if (num < den)
        smallest = num;
    else
        smallest = den;
    for (int i = 1; i < smallest; i++)
    {
        if (((smallest / i) == i) && ((smallest % i) == 0))
            root = i;
        else if (i + 1 == smallest)
            root = i + 1;
    }
    for (int j = root; j != 1; --j)
    {
        if ((num % j == 0) && (den % j) == 0)
        {
            den = den / j;
            num = num / j;
        }
    }
}

/******************************* OPERATOR METHODS ********************************/

fraction *fraction::operator=(const fraction &f)
{
    num = f.num;
    den = f.den;
    normal();
    return this;
}

fraction &fraction::operator+(int x)
{
    num += x * den;
    normal();
    return *this;
}

fraction &fraction::operator-(int x)
{
    num -= x * den;
    normal();
    return *this;
}

void fraction::operator+=(int x)
{
    *this = *this + x;
    normal();
}

void fraction::operator-=(int x)
{
    *this = *this - x;
    normal();
}

void fraction::operator+=(fraction &f)
{
    *this = *this + f;
    normal();
}

void fraction::operator-=(fraction &f)
{
    *this = *this - f;
    normal();
}

fraction &fraction::operator++()
{
    num += den;
    normal();
    return *this;
}

fraction &fraction::operator--()
{
    num -= den;
    normal();
    return *this;
}

fraction &fraction::operator++(int x)
{
    *this = *this + 1;
    normal();
    return *this;
}

fraction &fraction::operator--(int x)

{
    *this = *this - 1;
    normal();
    return *this;
}

int fraction::operator==(fraction f)
{
    if ((num == f.getNum()) && (den == f.getDen()))
        return 1;
    return 0;
}

fraction &fraction::operator!()
{
    int temp = num;
    num = den;
    den = temp;
    normal();
    return *this;
}

int fraction::operator<(fraction f) // returns 1 if left smaller then right
{
    int left, right;
    left = num * f.den;
    right = f.num * den;
    if (left < right)
        return 1;
    return 0;
}

/***************************** OPERATOR FUNCTIONS *********************************/

fraction operator+(fraction &first, fraction &sec)
{
    fraction a((first.getNum() * sec.getDen()) + (first.getDen() * sec.getNum()), first.getDen() * sec.getDen());
    return a;
}

fraction operator+(int x, fraction &f)
{
    fraction a(f.getNum() + (x * f.getDen()), f.getDen());
    return a;
}

fraction operator-(fraction &first, fraction &sec)
{
    fraction a((first.getNum() * sec.getDen()) - (first.getDen() * sec.getNum()), first.getDen() * sec.getDen());
    return a;
}

fraction operator-(int x, fraction &f)
{
    fraction a(f.getNum() - (x * f.getDen()), f.getDen());
    return a;
}

istream &operator>>(istream &input, fraction &fr)
{
    int up = 0, down = 1, choose;
    float x;
    cout << endl
         << "To enter float, press 1" << endl
         << "To enter integer, press 2" << endl
         << "To enter a fraction, press 3" << endl,
        cin >> choose;
    if (choose == 1)
    {
        cout << endl
             << "Enter float number: ",
            cin >> x;
        fraction f(x);
        fr = f;
    }
    if (choose == 2)
    {
        cout << endl
             << "Enter integer: ",
            cin >> up;
        fraction f(up);
        fr = f;
    }
    if (choose == 3)
    {
        cout << endl
             << "Enter numerator: ",
            cin >> up;
        cout << endl
             << "Enter denominator: ",
            cin >> down;
        fraction f(up, down);
        fr = f;
    }

    return input;
}

ostream &operator<<(ostream &output, fraction &f)
{
    if (f.getDen() == 1)
        output << f.getNum();
    else
        output << f.getNum() << '/' << f.getDen();

    return output;
}

