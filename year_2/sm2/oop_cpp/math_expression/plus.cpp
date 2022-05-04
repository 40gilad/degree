#include "plus.h"
plus::plus(expression* ex_1, expression* ex_2)
{
	left = ex_1->get_ex();
	right = ex_2->get_ex();
	
}

plus::~plus()
{
}

double plus::calc()
{
	return (left->calc() + right->calc());
}

expression* plus::get_ex()
{
	return this;
}
