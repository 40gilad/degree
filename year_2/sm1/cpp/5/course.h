#pragma once
#include<iostream>
#include<string.h>
using namespace std;
class course
{
protected:
	string Cname;
	float Cgrade;
	int Ccredits;
	bool Chomework;
public:
	course();
	course(course&);
	course(string name,int creits);
	string& getCname();
	float getCgrade();
	int getCcredits();
	bool isHomework();
	void didhomework();
	void undohomework();
	void grade(float);
	void operator=(course);
	void setname(string&);
	void setgrade(float);
	void setcredits(int);
};

