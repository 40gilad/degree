#pragma once
#include "Forward.h"
class PowerForward :
    public Forward
{
public:
    PowerForward();
    PowerForward(string name, int age, int number, double height, int shoe);
    ~PowerForward();


    void setp_ratio() { p_ratio = (double)p_blocks / p_score; }
    double getp_ratio() { return p_ratio; }


    void print();
    void Shoot(ShootType shoot, bool s_success);
    void Assist();
    void Block();

    PowerForward& operator=(const PowerForward player);
    bool operator<(PowerForward& player);
    bool operator>(PowerForward& player);
private:
    double p_ratio;
};

