#pragma once
#include "bin_expression.h"
class plus :
    public bin_expression
{
    public:
    plus(expression* ex_1, expression* ex_2);
    ~plus();
    double calc();
    expression* get_ex();
};

