#pragma once
#include"Process.h"

void Process::start() {
	return;
}
void Process::init() {
	settings = new Settings();
	game = new Game(settings);
	game->init();
	menu = new Menu();
	settings->init();
	menu->addField({ "Start Game", [&]{game->start(); } });
	menu->addField({ "Options", [&]{settings->start(); /*cls(); cout << "Sorry. Thats Unavaliable Right Now"; Sleep(1000); */} });
	menu->addField({ "Exit", [&]{exit(0);}});
	menu->start(false);
}
Process::~Process() {
	delete menu;
	delete game;
	delete settings;
}