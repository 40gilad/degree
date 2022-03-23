#pragma once
#include"person.h"
using namespace std;
class faculty
{
protected:
	string Fname;
	string FH_name;
	int floor;
	int Fcredits;
	float sch_grade;
public:
	faculty();
	faculty(faculty&);
	faculty(string, string, int, int, float);
	void CheckScholarshipConditions(float grade);
	string& getFname();
	string& getFH_name();
	int gtfloor();
	int getcredits();
	float getsch_grade();
	void operator=(faculty&);
};

