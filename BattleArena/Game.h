#pragma once

#include "Entity.h"
#include "Sort.h"
#include "Menu.h"

using namespace BetterSort;
using namespace game;

class Game
{
	int EnemyCount = 50;
	entity Character;
	entity* Enemies;
	Menu* menu;
public:
	Game();
	void Draw();
	void Update();
	~Game();
};

