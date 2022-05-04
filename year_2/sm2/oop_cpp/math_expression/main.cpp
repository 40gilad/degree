#include<iostream>
#include "number.h"
#include "bin_expression.h"
int main() {
	/*number* a = new number(3.2);
	number* b = new number(1.3);
	plus* c = new plus(a, b);
	std::cout << c->calc();*/
	///*minus* d= new minus(a, b);*/
	///*mul* e=new mul(new plus(new number(3.2),new number(1.3)),
	//	new minus(new number(5.4),new number(1.4)));
	//std::cout<<e->calc();*/
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