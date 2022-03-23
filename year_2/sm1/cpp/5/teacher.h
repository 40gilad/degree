#pragma once
#include "t_assistant.h"
using namespace std;
class teacher :public t_assistant
{
public:
	teacher();
	teacher(string s_name, int s_age, float s_hight, float s_weight,
		string f_name, string fh_name, int floor, int f_credits, float scolargrade, 
		string, int, course&);
	void gradeStudent(student&, float);
	void operator=(teacher &t);
	
};

