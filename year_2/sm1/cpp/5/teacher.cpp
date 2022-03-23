#include "teacher.h"

teacher::teacher() :
	t_assistant::t_assistant()
{
}

teacher::teacher(string s_name, int s_age, float s_hight, float s_weight,
	string f_name, string fh_name, int floor, int f_credits, float scolargrade,
	string s, int x, course& c) :
	t_assistant::t_assistant(s_name,s_age,s_hight, s_weight,
		f_name,fh_name, floor, f_credits, scolargrade,
		s,x, c)

{
}


void teacher::gradeStudent(student& s, float grade)
{
	if (s.IsStudying(TA_corse.getCname()))
		s.grade(grade, TA_corse);
	else
		cout << "\nStudent isnt learning this course! " << endl;
	
}

void teacher::operator=(teacher &t)
{
	t_assistant::operator=(t);
}
