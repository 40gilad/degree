#pragma once
#include "Guard.h"
class PointGuard :
    public Guard
{
public:
    PointGuard();
    PointGuard(string name, int age, int number,double height, int shoe);
    ~PointGuard();

    void setp_ratio() { p_ratio = (double)p_assists / p_score; }

    void print();
    void Shoot(ShootType shoot, bool s_success);
    void Assist();
    void Block();
    PointGuard& operator=(const PointGuard player);
    bool operator<(PointGuard& player);
    bool operator>(PointGuard& player);
private:
    double p_ratio;
};

