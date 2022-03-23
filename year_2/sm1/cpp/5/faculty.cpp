#include "faculty.h"

faculty::faculty():
Fname(""),FH_name(""), floor(-1), Fcredits(-1), sch_grade(-1)
{
}

faculty::faculty(faculty& f) :
	Fname(f.Fname), FH_name(f.FH_name), floor(f.floor), Fcredits(f.Fcredits), sch_grade(f.sch_grade)
{
}

faculty::faculty(string name, string f_FHname, int floor, int credits, float sch_grade):
	Fname(name), FH_name(f_FHname), floor(floor), Fcredits(Fcredits), sch_grade(sch_grade)
{
}

void faculty::CheckScholarshipConditions(float grade)
{
	if (grade >= sch_grade)
		cout << "\n student stands in the conditions for a sholarship" << endl;
}


string& faculty::getFname()
{
	return Fname;
}

string& faculty::getFH_name()
{
	return FH_name;
}

int faculty::gtfloor()
{
	return floor;
}

int faculty::getcredits()
{
	return Fcredits;
}

float faculty::getsch_grade()
{
	return sch_grade;
}

void faculty::operator=(faculty& f)
{
	this->Fcredits = f.Fcredits;
	this->FH_name = f.FH_name;
	this->floor = f.floor;
	this->Fname = f.Fname;
	this->sch_grade = f.sch_grade;
}

