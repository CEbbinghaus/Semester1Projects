#pragma once
#include<cmath>
#include"Menu.h"
#include "KeyHandler.h"



void Menu::addField(field o) 
{
	IField f(o);
	size++;
	options.push_back(o);
}

void Menu::addField(IField o)
{
	size++;
	options.push_back(o);
}

void Menu::setCursor(int pos) {
	cursor = pos;
	cursor = cursor < 0 ? 0 : cursor > size - 1 ? size - 1 : cursor;
}

void Menu::select(int index) 
{
	if (canExit)
		handler.stop();
	options[index].func();
	//update();
}

void Menu::start(bool exit) {
	this->canExit = exit;
	draw();
	tick();
}

void Menu::update() {
	cursor = cursor < 0 ? 0 : cursor > size - 1 ? size - 1 : cursor;
	draw();
}

void Menu::init(){}

void Menu::tick() {
	handler.on(keyCode::down, [&]() {cursor++; });
	handler.on(keyCode::up, [&]() {cursor--; });
	handler.on(keyCode::enter, [&]() {select(cursor);});
	handler.on(keyCode::space, [&]() {select(cursor); });
	handler.on(keyCode::esc, [&]() {handler.stop();});
	handler.on(keyCode::bspc, [&]() {handler.stop();});
	handler.on(handler.update, [&]() {update();});
	handler.start();
}
void Menu::draw() {
	cls();
	cout << "Menu" << endl;
	for (auto& i : options) {
		bool selected = &options[cursor] == &i;
		cout << "[" << (selected ? (char)178 : ' ') << ']';
		cout << i.name().c_str() << endl;
	}
}