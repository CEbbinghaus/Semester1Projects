#pragma once
#include <iostream>

namespace game {
	class entity
	{
	public:
		//Entity Properties
		float health; //Min-0 || Max-200
		float damage; //Min-0 || Max-500
		float shield; //Min-0 || Max-200
		float strength; //Min-0 || Max-100
		float agility; //Min-0 || Max-100
		float incentive; //Min-0 || Max-10
		float xp; //Min-0 || Max-Infinity
		int level; //Min-0 || Max-Inifnity

		bool hasAttacked = false;
		bool isDead = false;

		void attack(entity& target);
		void takeDamage(entity&  attacker, float amount);
		void draw();

		entity();
		entity(int level);
		~entity();
	};
	struct MAX_VALUE {
		static const int MAX_HEALTH = 200;
		static const int MAX_DAMAGE = 500;
		static const int MAX_SHIELD = 200;
		static const int MAX_STRENGTH = 100;
		static const int MAX_AGILITY = 100;
		static const int MAX_INCENTIVE = 10;
	};
}

