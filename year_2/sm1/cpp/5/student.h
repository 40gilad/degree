#pragma once
#include "person.h"
#include "faculty.h"
#include"course.h"
using namespace std;
class student :public faculty, public person
{private:
	string email;
	course Carr[10];
	int credits;

public:
	student();
	student(string s_name, int s_age, float s_hight, float s_weight,
		string f_name, string fh_name, int floor, int f_credits,float scolargrade,
		 string s_email, int s_credits);
	student(student&);
	string& getSemail();
	int getScredits();
	bool IsStudying(string course);
	float AVG();
	void DoHomeWork(course&);
	void Undohomework(course&);
	void grade(float,course&);
	void setCorse(course&);
	void operator=(student&);
};

