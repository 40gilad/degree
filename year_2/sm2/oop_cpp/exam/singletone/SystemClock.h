#pragma once
#include "Clock.h"
class systemclock {
private:
	static Clock* c;
	systemclock();
public:
	static Clock Getinstance();
	~systemclock();
};
Clock* systemclock::c = nullptr;

Clock systemclock::Getinstance() {
	if (!c)
		c = new Clock(11, 31);
	return *c;
}
systemclock::~systemclock() {
	delete c;
}


















//class SystemClock {
//private:
//	static Clock* clk;
//	SystemClock();
//public:
//	static Clock GetInstance();
//	~SystemClock();
//};
//
//Clock* SystemClock::clk = 0;
//
//Clock SystemClock::GetInstance() {
//	if (!clk)
//		clk = new Clock(10, 33);
//	return *clk;
//}
//SystemClock::~SystemClock() {
//	delete clk;
//}