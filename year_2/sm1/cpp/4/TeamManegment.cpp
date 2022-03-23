#include "TeamManegment.h"
using namespace std;

/****************************** CINSTRUCTORS **********************/

teamManegment::teamManegment() : arr(new Player *[10]), size(10), Open5(), amount(0)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = nullptr;
        if (i == 5)
            Open5[i] = nullptr;
    }
}

teamManegment::teamManegment(Player *parr[]) : arr(nullptr), size(0), amount(0)
{
    while (parr[amount++])
    {
    }
    size = amount;
    while (parr[size++] == nullptr)
    {
    }
    arr = parr;
    --amount;
    --size;
    for (int i = 0; i < 5; i++)
        Open5[i] = nullptr;
}

void teamManegment::setNewPlayer(Player *Nplayer)
{
    if (amount == size)
    {
        Player **newarr = new Player *[size * 2];
        for (int i = 0; i < size * 2; i++)
            newarr[i] = nullptr;
        for (int i = 0; i < size; i++)
            newarr[i] = arr[i];
        arr = newarr;
    }

    Player *p = dynamic_cast<PointGuard *>(Nplayer);
    if (p == nullptr)
        p = dynamic_cast<ShootingGuard *>(Nplayer);

    if (p == nullptr)
        p = dynamic_cast<SmallForward *>(Nplayer);

    if (p == nullptr)
        p = dynamic_cast<PowerForward *>(Nplayer);
    if (p != nullptr)
        arr[(amount++)] = p;
    else
        cout << "\nERROR CASTING TO PLAYER*" << endl;
}

void teamManegment::printArr()
{
    cout << "\nYour team:" << endl;
    for (int i = 0; i < amount; i++)
    {
        arr[i]->print();
        cout << endl;
    }
}

void teamManegment::printOpen5()
{
    cout << "\nYour open five:" << endl;
    for (int i = 0; i < 5; i++)
    {
        arr[i]->print();
        cout << endl;
    }
}

void teamManegment::printTeamStats()
{
}

void teamManegment::printTeamPoints()
{
}

void teamManegment::setOpenFive()
{
    int temp = 0;
    for (int i = 0; i < 5; i++)
    {
        cout << "\n Shitrt number of the player " << i + 1 << "/5: " << endl;
        cin>>temp;
        for (int j = 0; j < amount; j++)
        {
            cout << "\n shirt num in i= " << arr[j]->getp_number() << endl;
            cout << "\ntemp= " << temp;
            if (arr[j]->getp_number() == temp)
            {
                cout << "\nFount!" << endl;
                Open5[i] = arr[j];
            }
        }
    }
}

void teamManegment::changeOpenFive(int in, int out)
{
}
teamManegment::~teamManegment()
{
}