#include "number.h"

number::number()
{
    val = 0.0;
}

number::number(double num)
{
    val = num;
}

double number::calc()
{
    return val;
}
