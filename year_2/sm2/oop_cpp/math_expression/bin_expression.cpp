#include "bin_expression.h"

bin_expression::bin_expression()
{
	left = nullptr;
	right = nullptr;
}

expression* bin_expression::get_ex()
{
	return this;
}

/****************************** PLUS ******************************/

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

/****************************** MINUS ******************************/
minus::minus(expression* ex_1, expression* ex_2)
{
	left = ex_1->get_ex();
	right = ex_2->get_ex();

}

minus::~minus()
{
}

double minus::calc()
{
	return (left->calc() - right->calc());
}

expression* minus::get_ex()
{
	return this;
}

/****************************** DIV ******************************/

divide::divide(expression* ex_1, expression* ex_2)
{
	left = ex_1->get_ex();
	right = ex_2->get_ex();

}

divide::~divide()
{
}

double divide::calc()
{
	return (left->calc() / right->calc());
}

expression* divide::get_ex()
{
	return this;
}

/****************************** MUL ******************************/

mul::mul(expression* ex_1, expression* ex_2)
{
	left = ex_1->get_ex();
	right = ex_2->get_ex();

}

mul::~mul()
{
}

double mul::calc()
{
	return (left->calc() * right->calc());
}

expression* mul::get_ex()
{
	return this;
}
