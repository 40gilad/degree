#include "Player.h"

Player::Player()
	:p_name(""),p_age(0), p_number(0), p_height(0), p_shoe(0), p_blocks(0), p_assists(0),
	 p_fouls(0), p_two_p(0), p_three_p(0), p_two_s(0), p_three_s(0), p_score(0)
{
}

Player::Player(string name,int age, int number, double height, int shoe)
	: p_name(""),p_age(0), p_number(0), p_height(0), p_shoe(0), p_blocks(0), p_assists(0),
	p_fouls(0), p_two_p(0), p_three_p(0), p_two_s(0), p_three_s(0), p_score(0)
{
	setp_name(name);
	setp_age(age);
	setp_number(number);
	setp_height(height);
	setp_shoe(shoe);

}

Player::~Player()
{
}

Player::Player(const Player& player)
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
}


void Player::setp_age(int age)
{
	if(age<15 || age >40)
	{
		cout << "Invalide age"<<endl;
		return;
	}
	p_age = age;
}

void Player::Foul()
{
	p_fouls++;
	if(p_fouls>=5)
	cout<<"\n"<<p_name<<"has "<<p_fouls<<" fouls!!"<<endl;
}



void Player::print()
{
	cout << "Player detailes: " << endl;
	cout << "Name: " << p_name << endl;
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

void Player::enter(istream& in)
{
	string name;
	int temp;
	double temp2;
	int twos, threes;
	cout << "Please enter the player name : ";
	in >> name;
	setp_name(name);
	cout<< endl << "Please enter the player age: ";
	in >> temp;
	setp_age(temp);
	cout << endl << "Please enter the player height : ";
	in >> temp2;
	setp_height(temp);
	cout << endl << "Please enter the player number: ";
	in >> temp;
	setp_number(temp);
	cout << endl << "Please enter the player shoe size: ";
	in >> temp;
	setp_shoe(temp);
	cout << endl << "Please enter the player number of blocks made: ";
	in >> temp;
	setp_blocks(temp);
	cout << endl << "Please enter the player number of assists made: ";
	in >> temp;
	setp_assists(temp);
	cout << endl << "Please enter the player amount of fouls made: ";
	in >> temp;
	setp_fouls(temp);
	cout << endl << "Please enter the player number of two pointer throws made:  ";
	in >> temp;
	setp_two_p(temp);
	cout << endl << "Please enter the player number of two pointer throw scored: ";
	in >> temp;
	setp_two_s(temp);
	cout << endl << "Please enter the player number of three pointer throws made:  ";
	in >> temp;
	setp_three_p(temp);
	cout << endl << "Please enter the player number of three pointer throw scored: ";
	in >> temp;
	setp_three_s(temp);
	twos = getp_two_s();
	threes = getp_three_s();
	setp_score(twos*2 + threes*3);
}

bool Player::operator>(Player& player)
{
	double p1_ratio = getp_score() / getp_assists();
	double p2_ratio =(double) player.getp_score() / player.getp_assists();
	if (p1_ratio > p2_ratio)
		return true;
	else
		return false;
}


bool Player::operator<(Player& player)
{
	double p1_ratio = getp_score() / getp_assists();
	double p2_ratio = player.getp_score() / player.getp_assists();
	if (p1_ratio < p2_ratio)
		return true;
	else
		return false;
}

// ostream& operator<<(ostream& cout, Player& player)
// {
// 	player.print(cout);
// 	return cout;
// }

istream& operator>>(istream& cin, Player& player)
{
	player.enter(cin);
	return cin;
}



Player& Player::operator=(const Player& player)
{
	//Player(player);
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