#define _USE_MATH_DEFINES
#include <string>
#include <cmath>
#include <random>
#include "entity.h"


using namespace game;
using namespace std;

float rando() {
	return (rand() % 10000) / 10000;
}

entity::entity()
{
	health = rando() * (MAX_VALUE::MAX_HEALTH * 0.1);
	damage = rando() * (MAX_VALUE::MAX_DAMAGE * 0.1);
	shield = rando() * (MAX_VALUE::MAX_SHIELD * 0.1);
	strength = rando() * (MAX_VALUE::MAX_STRENGTH * 0.1);
	agility = rando() * (MAX_VALUE::MAX_AGILITY * 0.1);
	incentive = rando() * (MAX_VALUE::MAX_INCENTIVE * 0.1);
	xp = 0;
	level = round(rando() * 10);
}

entity::entity(int a_level)
{
	float mod = 1 - pow(M_E, (double)(-0.02 * level));
	health = rando() * (MAX_VALUE::MAX_HEALTH * mod);
	damage = rando() * (MAX_VALUE::MAX_DAMAGE * mod);
	shield = rando() * (MAX_VALUE::MAX_SHIELD * mod);
	strength = rando() * (MAX_VALUE::MAX_STRENGTH * mod);
	agility = rando() * (MAX_VALUE::MAX_AGILITY * mod);
	incentive = rando() * (MAX_VALUE::MAX_INCENTIVE * mod);
	xp = 0;
	level = a_level;
}

void entity::attack(entity& enemy) {
	//TODO: Calculate Damage done by the entity with damage / strength and
	int actualDMG = (strength / MAX_VALUE::MAX_STRENGTH) * MAX_VALUE::MAX_DAMAGE;
	enemy.takeDamage(*this, actualDMG);
}

void entity::takeDamage(entity& attacker, float amount) {
	bool dodged = (attacker.agility / agility) < 0; //TODO randomize number and multiply to get dodge chance.
	int actualDamage = (amount / shield) * (1000 / strength);
	int actualShield = shield - (amount / shield) * 100;
	if (actualShield <= 0)
		actualDamage = damage - shield;
	health -= actualDamage;
	shield = actualShield;
}

string formatStat(int v) {
	float size = (to_string(v).length() - 6) / 2;
	size = size < 0 ? 0 : size;
	string r = "";
	int i = 0;

	for (i = 0; i < floor(size); i++)
		r += " ";
	r += to_string(v);
	for (i = 0; i < ceil(size); i++)
		r += " ";
	return r;
}
string formatStat(float v) {
	float size = (to_string(round(v)).length() - 6) / 2;
	size = size < 0 ? 0 : size;
	string r = "";
	int i = 0;

	for (i = 0; i < floor(size); i++)
		r += " ";
	r += to_string(round(v));
	for (i = 0; i < ceil(size); i++)
		r += " ";
	return r;
}

void entity::draw() {
	system("cls");
	cout << "╔══════════════════╦══════╗\n"
		 << "║    CHARACTER     ║ STATS║\n"
		 << "╠══════════════════╬══════╣\n";
	cout << "║     Health       ║"<< formatStat(health) <<"║\n"
		 << "╟──────────────────╫──────╢\n";
	cout << "║     Shield       ║"<< formatStat(shield) <<"║\n"
		 << "╟──────────────────╫──────╢\n";
	cout << "║    Incentive     ║"<< formatStat(incentive) <<"║\n"
		 << "╟──────────────────╫──────╢\n";
	cout << "║     Agility      ║"<< formatStat(agility) <<"║\n"
		 << "╟──────────────────╫──────╢\n";
	cout << "║    Strength      ║"<< formatStat(strength) <<"║\n"
		 << "╟──────────────────╫──────╢\n";
	cout << "║     Damage       ║"<< formatStat(damage) <<"║\n"
		 << "╚══════════════════╩══════╝";
	/*

	float health; //Min-0 || Max-200

		float xp; //Min-0 || Max-Infinity
		int level; //Min-0 || Max-Inifnity
╔══════════════════╦════════════════════╗
║    CHARACTER     ║       STATS        ║
╠══════════════════╬══════╤══════╤══════╣
║     Health       ║                    ║
╟──────────────────╫──────┼──────┼──────╢
║     Shield       ║                    ║
╟──────────────────╫──────┼──────┼──────╢
║    Incentive     ║                    ║
╟──────────────────╫──────┼──────┼──────╢
║     Agility      ║                    ║
╟──────────────────╫──────┼──────┼──────╢
║    Strength      ║                    ║
╟──────────────────╫──────┼──────┼──────╢
║     Damage       ║                    ║
╚══════════════════╩══════╧══════╧══════╝
	*/
}

entity::~entity()
{
}
