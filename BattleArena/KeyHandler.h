#pragma once
#include<iostream>
#include<conio.h>
#include<functional>
#include<map>

using namespace std;

struct keyCode
{
	static const int up = 72;
	static const int down = 80;
	static const int left = 75;
	static const int right = 77;
	static const int enter = 13;
	static const int space = 32;
	static const int esc = 27;
	static const int bspc = 8;
};

class KeyHandler
{
	map<char, function<void()>> keys;
	bool handling = false;
	void handleInput();
public:
	static const int update = 7;
	void start();
	void stop();
	void init();
	void on(char character, function<void()> handler);
	char subscribeToEvent();
};