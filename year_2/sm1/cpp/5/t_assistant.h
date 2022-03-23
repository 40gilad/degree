#pragma once
#include "student.h"
using namespace std;
 class t_assistant:public person,public faculty
{	protected:
	string TA_email;
	int TA_salary;
	course TA_corse;
public:
	t_assistant();
	t_assistant(t_assistant&);
	t_assistant(string s_name, int s_age, float s_hight, float s_weight,
		string f_name, string fh_name, int floor, int f_credits, float scolargrade, 
		string email, int salary, course& course);
	void WriteHomework(student&);
	void operator=(t_assistant&);
};

