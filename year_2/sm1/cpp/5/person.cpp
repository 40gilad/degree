
#include "person.h"

person::person() :
	name(""), age(-1), hight(-1), weight(-1)
{
}

person::person(person& p):
	name(p.name), age(p.age), hight(p.hight), weight(p.weight)
{
}

person::person(string p_name, int p_age, float p_hight, float p_weight) :
	name(p_name), age(p_age), hight(p_hight), weight(p_weight)
{
	while (age > 120 || age < 18) {
		cout << "\n age is not in range! \nplease enter a new one: " << endl;
		cin >> age;
	}
	while (hight > 250) {
		cout << "\n hight is not in range! \nplease enter a new one: " << endl;
		cin >> hight;
	}
}

string& person::getPname()
{
	return name;
}

int person::getage()
{
	return age;
}

float person::gethight()
{
	return hight;
}

float person::getweight()
{
	return weight;
}

void person::operator=(person&p)
{
	name = p.name;
	age = p.age;
	weight = p.weight;
	hight = p.hight;
}

