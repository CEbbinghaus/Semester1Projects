#pragma once
#include "Scaffold.h"
#include "Game.h"
#include "Menu.h"
#include "Settings.h"

struct Process : public BaseStructure {
	Menu* menu;
	Game* game;
	Settings* settings;

	~Process();
	void start();
	void init();
};