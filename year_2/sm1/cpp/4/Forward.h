#pragma once
#include "Player.h"
class Forward :
    public Player
{
public:
    Forward();
    Forward(string name, int age, int number, double height, int shoe);
    virtual ~Forward();
    virtual void print(Forward Player){};
    virtual void Shoot(ShootType shoot, bool s_success) {};
    virtual void Assist() {};
    virtual void Block() {};
private:
};

