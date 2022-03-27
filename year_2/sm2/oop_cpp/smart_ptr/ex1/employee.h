#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
#pragma once
class employee
{public:
	employee();
	employee(string& _id, int _salary, int _seniority);
	friend ostream& operator<<(ostream& out, employee& source);
	friend istream& operator>>(istream& in, employee& dest);
	string& getid() {return id;}
	int getsalary() { return salary; }
	int getsen() { return seniority; }
	void setid(string& _id) { id = _id; }
	void setsalary(int sal) { salary = sal; }
	void setsenior(int sen) { seniority = sen; }
	employee& operator=(employee& emp);
	employee& load();
	void save();
private:
	string id;
	int salary;
	int seniority;
};

