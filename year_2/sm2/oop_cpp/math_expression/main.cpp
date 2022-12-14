#include<iostream>
#include "number.h"
#include "bin_expression.h"

/*********************** GILAD MEIR - 313416562 ***********************/
/*********************** ROEY BEN HARUSH- 315676163 ******************/
int main() {
	expression* ex = 
		new plus(new divide
		(new number(10), 
			new number(2)), 
			new mul
			(new number(2), 
				new minus
				(new number(3), 
					new number(4))));
	std::cout << ex->calc();
}