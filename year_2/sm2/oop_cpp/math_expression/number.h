#pragma once
#include "expression.h"
class number :
    public expression
{
    double val;
public:
    ~number(){}
    number(double num);
    double calc();
    number();
    expression* get_ex() {
        return this;
    }
};

