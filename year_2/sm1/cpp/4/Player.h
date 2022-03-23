#pragma once
#include <iostream>
#include <string.h>
using namespace std;

enum class ShootType
{
	threePoint, twoPoint
};


class Player
{
public:
	Player();
	Player(string name,int age, int number, double height, int shoe);
	virtual ~Player();
	Player(const Player& player);
public:
	string getp_name()const			{ return p_name;	}
	int getp_age()const				{ return p_age;		}
	int getp_number()const			{ return p_number;	}
	double getp_height()const		{ return p_height;	}
	int getp_shoe()const			{ return p_shoe;	}
	int getp_blocks()const			{ return p_blocks;	}
	int getp_assists()const			{ return p_assists; }
	int getp_fouls()const			{ return p_fouls;	}
	int getp_two_p()const			{ return p_two_p;	}
	int getp_three_p()const			{ return p_three_p; }
	int getp_two_s()const			{ return p_two_s;	}
	int getp_three_s()const			{ return p_three_s; }
	int getp_score()const			{ return p_score;	}
public:
	void setp_name(string name)		{ p_name = name;		}
	void setp_age(int age);
	void setp_number(int number)	{ p_number = number;	}
	void setp_height(double hight)	{ p_height = hight;		}
	void setp_shoe(int shoe)		{ p_shoe = shoe;		}
	void setp_blocks(int blocks)	{ p_blocks = blocks;	}
	void setp_assists(int assists)	{ p_assists = assists;	}
	void setp_fouls(int fouls)		{ p_fouls = fouls;		}
	void setp_two_p(int two_p)		{ p_two_p = two_p;		}
	void setp_three_p(int three_p)	{ p_three_p = three_p;	}
	void setp_two_s(int two_s)		{ p_two_s = two_s;		}
	void setp_three_s(int three_s)	{ p_three_s = three_s;	}
	void setp_score(int score)		{ p_score = p_three_s * 3 + p_two_s * 2; }
public:
	 void Foul();				//{ p_fouls++;			}
	virtual void Assist(){}; /* { p_assists++;
					if (p_assists >= 11) 
						std::cout << " Great Job! keep assisting!";			}*/
	virtual void Block(){};/* { p_blocks++;
					if(p_blocks >= 11)
						std::cout << " Great Job! keep blocking!";			}*/
	virtual void Shoot(ShootType shoot, bool s_success){};
	virtual void print();
	void enter(istream& in = cin);
	bool operator>(Player& player);
	bool operator<(Player& player);
	Player& operator=(const Player& player);

protected:
	string p_name;				// the player name
	int p_age;					// the player age
	int p_number;				// the player shirt number
	double p_height;				// the player hight
	int p_shoe;					// the player shoe size
	int p_blocks;				// the amount of blocks the player did
	int p_assists;				// the amount of assists the player did
	int p_fouls;				// the amount of fouls the player did
	int p_two_p;				// the amount of 2 pointers shots the player did
	int p_three_p;				// the amount of 3 pointers shots the player did
	int p_two_s;				// the amount of 2 pointers shots the player scored
	int p_three_s;				// the amount of 3 pointers shots the player scored
	int p_score;				// the overall score the player has scored
private:

};


ostream& operator<<(ostream& cout, Player& player);
istream& operator>>(istream& cin, Player& player);

