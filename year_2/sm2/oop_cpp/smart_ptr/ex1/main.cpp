#pragma once
#include "cached_map.h"
#include <string>
#include "employee.h"
using namespace std;

int main() {
	string id[3] = { "123","456","789" };
	employee a(id[0], 20, 4);
	employee b(id[1], 30, 5);
	employee c(id[2], 40, 6);
	employee g[3];
	g[0] = a;
	g[1] = b;
	g[2] = c;
	/*g->save();*/
	a.save();
	a.load();
	
	
}