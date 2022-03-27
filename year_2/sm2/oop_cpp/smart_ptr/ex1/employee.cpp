#include "employee.h"


employee::employee() :
	id("\0"), salary(-1), seniority(-1) {}
employee::employee(string& _id, int _salary, int _seniority) :
	id(_id), salary(_salary), seniority(_seniority) {}
istream& operator>>(istream& in, employee& dest) {
	return in;
}
ostream& operator<<(ostream& out, employee& from) {

	return out;
}
employee& employee::operator=(employee& emp) {
	id = emp.getid();
	salary = emp.getsalary();
	seniority = emp.getsen();
	return *this;
}
employee& employee::load() {
	ifstream in("emps.bin", ios::binary);
	if (!in.is_open())
		throw "could'nt open file: emps.bin";
	ifstream infile("emp.bin", ifstream::binary);
	unsigned int size = 0;
	infile.read(reinterpret_cast<char*>(&size), sizeof(size));
	string buffer;
	buffer.resize(size);

	infile.read(&buffer[0], buffer.size());
	infile.close();
	return *this;
}
void employee::save() {
	ofstream out("emps.bin", ios::binary);
	char op = '[', cl = ']';

	if (!out.is_open())
		throw "could'nt open file: emps.bin";
	int x = 3;
	while (x) {
		string text;
		unsigned int size;
		if(x==3)
		 text = getid();
		if (x == 2)
			text = (char)getsalary();
		if (x == 1)
			text = (char)getsen();
		size = text.size();
		out.write((char*)&op, 1);
		out.write(reinterpret_cast<char*>(&size), sizeof(size));  // write it to the file
		out.write(text.c_str(), text.size());
		out.write((char*)&cl, 1);
		--x;
	}
	out.close();
}
