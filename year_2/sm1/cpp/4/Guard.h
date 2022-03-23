#pragma once
#include "player.h"

class Guard :
	public Player
{
public:
	Guard();
	Guard(string name, int age, int number, double height, int shoe);
	virtual ~Guard();

	virtual void print(Guard player){};
	virtual void Shoot(ShootType shoot, bool s_success){};
	virtual void Assist(){};
	virtual void Block(){};
private:

};