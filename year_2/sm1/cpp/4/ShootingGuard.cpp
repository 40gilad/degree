#include "ShootingGuard.h"

ShootingGuard::ShootingGuard() :p_ratio(0)
{

}

ShootingGuard::ShootingGuard(string name, int age, int number, double height, int shoe):Guard(name, age, number, height, shoe),p_ratio(0)
{
}


ShootingGuard::~ShootingGuard()
{
}

void ShootingGuard::print()
{
	setp_ratio();
	cout << "Player detailes: " << endl;
	cout << "Name: " << p_name << endl;
	cout << "Job : ShootingGuard" << endl;
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
	cout << "The player ratio of Blocks to Score: " << p_ratio << endl;
}

float ratio(int twop, int threep, int twos, int threes)
{
	int shoots = twop + threep, scored = twos + threes;
	if ((double)shoots /scored < 0.3)
		cout << "The player scored to shoots ratio is low!" << endl;
	return (double)shoots / scored;
}

void ShootingGuard::Shoot(ShootType shoot, bool s_success)
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
	setp_ratio();
	cout << ratio(p_two_p,p_three_p,p_two_s,p_three_s) << endl;
	if (ratio(p_two_p, p_three_p, p_two_s, p_three_s) < 0.3)
		cout << "The Player assists to score ratio is too low!" << endl;
}

void ShootingGuard::Assist()
{
	p_assists++;
		if(p_assists>=10)
		cout << "Great job!!! keep at it!" << endl;
}

void ShootingGuard::Block()
{
	p_blocks++;
	if(p_blocks>=10)
		cout << "Great job!!! keep at it!" << endl;
}

ShootingGuard& ShootingGuard::operator=(const ShootingGuard player)
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
	p_ratio = player.p_ratio;
	return *this;
}

bool ShootingGuard::operator<(ShootingGuard& player)
{
	if (p_ratio < player.p_ratio)
		return true;
	return false;
}

bool ShootingGuard::operator>(ShootingGuard& player)
{
	if (p_ratio > player.p_ratio)
		return true;
	return false;
}
