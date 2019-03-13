#include "Game.h"



Game::Game(){
	menu = new Menu();
	Enemies = new entity[EnemyCount];


	BetterSort::sort<entity>(Enemies, EnemyCount, [](entity e) {return round(e.health); });


	for (int i = 0; i < EnemyCount; i++) {
		entity e = Enemies[i];
		e.draw();
		_sleep(200);
	}
}

void Game::Update() {
}

void Game::Draw() {
	
}

Game::~Game()
{
	delete[] Enemies;
}
     