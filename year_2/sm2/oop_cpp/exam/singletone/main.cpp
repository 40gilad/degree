#include "SystemClock.h"
#include <iostream>
using namespace std;

int main()
{
	int i = 4;
	Clock arr[4];
	while(--i)
		arr[i] = systemclock::Getinstance();
	i = 5;
	while (--i)
		cout << "Clock num " << i << "=" << arr[i].getH() << ":" << arr[i].getM() << "\n";
}