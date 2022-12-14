#pragma once
#include <iostream>
using namespace std;
class Clock {
	int hour;
	int min;
public:
	inline Clock(int Nhour = 0, int Nmin = 0);
	int getH();
	int getM();
};
Clock::Clock(int nhour, int nmin) {
	hour = nhour;
	min = nmin;
}
int Clock::getH() {
	return hour;
}

int Clock::getM() {
	return min;
}