#include "TeamManegment.h"

int main()
{
    PowerForward pw("gilad", 26, 8, 175, 42);
    ShootingGuard pt("shiran asaf", 27, 15, 165, 39);
    SmallForward s("koop",60,14,170,43);
    PointGuard a("adam",28,7,180,43);
    PointGuard y("yona",30,99,180,44);
    Player *arr[2];
    for (int i = 0; i < 2; i++)
        arr[i] = nullptr;
    teamManegment tm(arr);
    tm.setNewPlayer(&pt);
    tm.setNewPlayer(&pw);
    tm.setNewPlayer(&s);
    tm.setNewPlayer(&a);
    tm.setNewPlayer(&y);
    tm.setOpenFive();
    tm.printOpen5();

}