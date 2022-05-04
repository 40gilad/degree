#include <iostream>
#include <math.h>
#pragma once
class expression
{public:
	expression(){}
	virtual ~expression(){}
	virtual double calc()=0;
	virtual expression* get_ex() = 0;
};

