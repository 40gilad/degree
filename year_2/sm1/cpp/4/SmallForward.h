#pragma once
#include "Forward.h"
class SmallForward :
    public Forward
{
    public:
    SmallForward();
    SmallForward(string name, int age, int number, double height, int shoe);
    ~SmallForward();

    SmallForward& operator=(const SmallForward player);
    void print();
    void Shoot(ShootType shoot, bool s_success);
    void Assist();
    void Block();

};
