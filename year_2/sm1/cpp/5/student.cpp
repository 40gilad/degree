#include "student.h"

student::student() :
	email(""), credits(-1)
{
}

student::student(string s_name, int s_age, float s_hight, float s_weight, 
	string f_name, string fh_name, int floor, int f_credits, float scolargrade,
	string s_email, int s_credits):

	person::person(s_name,s_age,s_hight,s_weight),
	faculty::faculty(f_name,fh_name,floor,f_credits,scolargrade),
	email(s_email),credits(s_credits)
{
		
}


student::student(student&s):
	email(s.email),credits(s.credits)
{
	name = s.name; age = s.age; hight = s.hight; weight = s.weight;
	Fname = s.Fname; FH_name = s.FH_name; floor = s.floor; Fcredits = s.Fcredits; sch_grade = s.sch_grade;
	for (int i = 0; Carr[i].getCcredits()!=-1; i++)
		Carr[i] = s.Carr[i];
}

string& student::getSemail()
{
	return email;
}

//course& student::getCarr()
//{
//	return Carr;
//}

int student::getScredits()
{
	return credits;
}

bool student::IsStudying(string corse)
{
	for (int i = 0; Carr[i].getCcredits() != -1; i++) {
		if (Carr[i].getCname() == corse)
			return true;	
	}
	return false;
}

float student::AVG()
{
	float avg = 0;
	int i = 0;

	for (; Carr[i].getCcredits()!=-1; i++)
		avg += Carr[i].getCgrade();
	return (avg /i);
}

void student::DoHomeWork(course& c)
{
	for (int i = 0; Carr[i].getCcredits() !=-1 ; i++) {
		if (Carr[i].getCname() == c.getCname())
			Carr[i].didhomework();
	}

}

void student::Undohomework(course&c)
{
	for (int i = 0; Carr[i].getCcredits() != -1; i++) {
		if (Carr[i].getCname() == c.getCname())
			Carr[i].undohomework();
	}
}

void student::grade(float g,course& c)
{
	for (int i = 0; i < 10; i++) {
		if (Carr[i].getCname() == c.getCname()) {
			if (Carr[i].isHomework() == false)
				Carr[i].grade(g);
			else Carr[i].grade(0);
			break;
		}
	}
}

void student::setCorse(course &c)
{
	course a(c);
	for (int i = 0; i < 10; i++) {
		if (Carr[i].getCcredits() == -1) {
			Carr[i] = a;
			break;
		}
	}
	
}

void student::operator=(student& s)
{
	for (int i = 0; s.Carr[i].getCcredits()!=-1; i++) {
		Carr[i]=s.Carr[i];
		Carr[i].setcredits(s.Carr[i].getCcredits());
		Carr[i].setgrade(s.Carr[i].getCgrade());
		Carr[i].setname(s.Carr[i].getCname());
	}
	
		credits = s.credits;
		email = s.email;
	faculty::operator=(s);
	person::operator=(s);
	
}
