#pragma once
#include "expression.h"
#include "number.h"
class bin_expression :
    public expression
{
protected:
    expression* left;
    expression* right;
public:
    bin_expression();
    virtual ~bin_expression(){}
    virtual double calc()=0;
    virtual expression* get_ex();
};

class plus :
    public bin_expression
{

public:
    plus(expression* ex_1, expression* ex_2);
    ~plus();
    double calc();
    expression* get_ex();
};

class minus :
    public bin_expression
{
public:
    minus(expression* ex_1, expression* ex_2);
    ~minus();
    double calc();
    expression* get_ex();
};

class divide :
    public bin_expression
{
public:
    divide(expression* ex_1, expression* ex_2);
    ~divide();
    double calc();
    expression* get_ex();
};

class mul :
    public bin_expression
{
public:
    mul(expression* ex_1, expression* ex_2);
    ~mul();
    double calc();
    expression* get_ex();
};
