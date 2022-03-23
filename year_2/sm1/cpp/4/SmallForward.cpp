#include "SmallForward.h"


SmallForward::SmallForward()
{

}

SmallForward::SmallForward(string name, int age, int number, double height, int shoe) : Forward(name, age, number, height, shoe)
{
	if(height<1.95)
	{
		cout << "The player is too short! please choose another player!" << endl;
		return;
	}

}

SmallForward::~SmallForward()
{
}

SmallForward& SmallForward::operator=(const SmallForward player)
{
	p_name = player.p_name;
	p_age = player.p_age;
	p_number = player.p_number;
	p_height = player.p_height;
	p_shoe = player.p_shoe;
	p_blocks = player.p_blocks;
	p_assists = player.p_assists;
	p_fouls = player.p_fouls;
	p_two_p = player.p_two_p;
	p_three_p = player.p_three_p;
	p_two_s = player.p_two_s;
	p_three_s = player.p_three_s;
	p_score = player.p_score;
	return *this;
}


void SmallForward::print()
{
	cout << "Player detailes: " << endl;
	cout << "Name: " << p_name << endl;
	cout << "Job : SmallForward" << endl;
	cout << "Age: " << p_age << endl;
	cout << "Number: " << p_number << endl;
	cout << "Height: " << p_height << endl;
	cout << "Shoe Size: " << p_shoe << endl;
	cout << "Number of blocks: " << p_blocks << endl;
	cout << "Number of assists: " << p_assists << endl;
	cout << "Number of fouls: " << p_fouls << endl;
	cout << "Number of Two pointer shots: " << p_two_p << endl;
	cout << "Number of two pointer scored: " << p_two_s << endl;
	cout << "Number of three pointer shots: " << p_three_p << endl;
	cout << "Number of three pointers scored: " << p_three_s << endl;
	cout << "Number of overall scored: " << p_score << endl;
}

void SmallForward::Shoot(ShootType shoot, bool s_success)
{
	switch (shoot)
	{
	case(ShootType::threePoint):
		p_three_p++;
		if (s_success)
		{
			p_three_s++;
			p_score += 3;
		}
		break;
	case(ShootType::twoPoint):
		p_two_p++;
		if (s_success)
		{
			p_two_s++;
			p_score += 2;
		}
		break;
	default:
		break;
	}
}

void SmallForward::Assist()
{
	p_assists++;
	if (p_assists >= 10)
		cout << "Great Job! Keep at it!" << endl;
}

void SmallForward::Block()
{
	p_blocks++;
	if (p_blocks >= 10)
		cout << "Great Job! Keep at it!" << endl;
}
