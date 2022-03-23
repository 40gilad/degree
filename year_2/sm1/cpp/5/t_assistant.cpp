#include "t_assistant.h"

t_assistant::t_assistant() :
	TA_email(""), TA_corse(),TA_salary(-1)
{
}

t_assistant::t_assistant(t_assistant&t):
	TA_email(t.TA_email),TA_corse(t.TA_corse),TA_salary(t.TA_salary)
{
}

t_assistant::t_assistant(string s_name, int s_age, float s_hight, float s_weight,
	string f_name, string fh_name, int floor, int f_credits, float scolargrade, 
	string s, int x, course& c):
	person::person(s_name, s_age, s_hight, s_weight),
	faculty::faculty(f_name, fh_name, floor, f_credits, scolargrade),
	TA_email(s), TA_corse(c), TA_salary(x)
{
}

void t_assistant::WriteHomework(student& s)
{
	s.Undohomework(TA_corse);
}

void t_assistant::operator=(t_assistant&ta)
{
	TA_email = ta.TA_email;
	TA_salary = ta.TA_salary;
	TA_corse = ta.TA_corse;
	person::operator=(ta);
	faculty::operator=(ta);
}


