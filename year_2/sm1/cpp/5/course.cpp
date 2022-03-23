#include "course.h"

course::course():
	Cname(""),Cgrade(0),Ccredits(-1),Chomework(false)
{
}

course::course(course& c):
	Cname(c.Cname),Cgrade(c.Cgrade),Ccredits(c.Ccredits),Chomework(c.Chomework)
{
	
}

course::course(string s,int c_credits) :
	Cname(s), Cgrade(-1), Ccredits(c_credits), Chomework(false)
{
	while (Ccredits > 5) {
		cout << "\n credits is not in range! \nplease enter a new one: " << endl;
		cin >>	Ccredits;
	}
}

string& course::getCname()
{
	return Cname;
}

float course::getCgrade()
{
	return Cgrade;
}

int course::getCcredits()
{
	return Ccredits;
}

bool course::isHomework()
{
	return Chomework;
}

void course::didhomework()
{
	if (Chomework)
	Chomework = false;
}

void course::undohomework()
{
	if (!Chomework)
		Chomework = true;

}

void course::grade(float x)
{
	Cgrade = x;
}

void course::operator=(course c)
{
	Cname = c.Cname;
	Cgrade = c.Cgrade;
	Ccredits = c.Ccredits;
	Chomework = c.Chomework;

}

void course::setname(string& s)
{
	Cname = s;
}

void course::setgrade(float f)
{
	Cgrade = f;
}

void course::setcredits(int i)
{
	Ccredits = i;
}


