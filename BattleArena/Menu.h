#pragma once
#include <iostream>
#include <vector>
#include "KeyHandler.h"

using namespace std;

struct field {
	string name;
	function<void()> func;
};

struct IField {
	function<string()> name;
	function<void()> func;
	IField(function<string()> a_name, function<void()> a_func) {
		name = a_name;
		func = a_func;
	}
	IField(field origin) {
		func = origin.func;
		name = [=]() {return origin.name;};
	}
};

class Menu {
	bool canExit = false;
	int cursor = 0;
	KeyHandler handler;
	vector<IField> options;
	int size = 0;

public:
	void addField(field o);
	void addField(IField o);
	void cls();
	void select(int index);
	void start(bool exit = true);
	void setCursor(int pos);
	void init();
	void tick();
	void draw();
	void update();
};