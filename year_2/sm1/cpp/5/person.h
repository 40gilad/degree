#pragma once
#include <iostream>
#include <string.h>
using namespace std;
class person
{
protected:
	string name;
	int age;
	float hight;
	float weight;

public:
	person();
	person(person&);
	person(string, int, float, float);
	string& getPname();
	int getage();
	float gethight();
	float getweight();
	void operator=(person&);

};



