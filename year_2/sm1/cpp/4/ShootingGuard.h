#pragma once
#include "Guard.h"
class ShootingGuard : public Guard
{
public:
    ShootingGuard();
    ShootingGuard(string name, int age, int number, double height, int shoe);
    ~ShootingGuard();

    void setp_ratio() { p_ratio = (double)(p_two_p + p_three_p) / (p_two_s + p_three_s); }
    double getp_ratio() { return p_ratio; }

    virtual void print();
    void Shoot(ShootType shoot, bool s_success);
    void Assist();
    void Block();

    ShootingGuard &operator=(const ShootingGuard player);
    bool operator<(ShootingGuard &player);
    bool operator>(ShootingGuard &player);

private:
    double p_ratio;
};
