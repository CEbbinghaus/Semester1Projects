#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

#include "FileIO.h"
#include "Menu.h"
#include "util.h"


using namespace std;


enum VType {
	UDef = 0,
	Str = 1,
	Int = 2,
	Flt = 3,
	Bll = 4
};

class Option:public BaseStructure{
public:
	int type = VType::UDef;
	string name;
	virtual void configure() = 0;
	virtual void* Value() = 0;
	virtual void write(stringstream& buffer) = 0;
	virtual void read(stringstream& buffer) = 0;
	virtual string draw() = 0;
};

class SOption : public Option {
public:
	char* value;
	vector<string> possibilities;
	SOption(string a_name, const char* a_value, vector<string> options) {
		type = VType::Str;
		name = a_name;
		possibilities = options;
		value = new char[32];
		strcpy(value, a_value);
	}
	~SOption() {
		delete value;
		value = nullptr;
	}
	void* Value() {
		return value;
	}
	void write(stringstream& buffer) {
		buffer << value;
		buffer << '\0';
	}
	void read(stringstream& buffer) {
		buffer.clear();
		buffer.get(value, 32, '\0');
		buffer.seekg(1, ios::cur);
		cout << value;
	}
	string draw() {
		return name + ": " + value;
	}
	void configure() {
		Menu m;
		for (string s : possibilities) {
			m.addField({ s, [=]() {strcpy(value, s.c_str());} });
		}
		
		auto currentValue = find(possibilities.begin(), possibilities.end(), string(value));
		if (currentValue != possibilities.end())
			m.setCursor(distance(possibilities.begin(), currentValue));
		m.draw();
		Sleep(200);
		m.start();
	}
};

class IOption : public Option {
public:
	int* value;
	int min;
	int max;
	IOption(string a_name, int a_value, int a_min, int a_max) {
		type = VType::Int;
		name = a_name;
		value = new int(a_value);
		min = a_min;
		max = a_max;
	}
	~IOption() {
		delete value;
		value = nullptr;
	}
	void* Value() {
		return value;
	}
	void write(stringstream& buffer) {
		buffer.write((const char*)(value), sizeof(int));
	}
	void read(stringstream& buffer) {
		buffer.clear();
		char data[5];
		buffer.get(data, 5);
		memcpy(value, data, 4);
	}
	string draw() {
		return name + ": " + to_string(*value);

	}
	void configure() {
		int width = (int)(ConsoleWidth() / 0.75);
		float step = 1 / width;
		int cursor = floor(((*value - min) / (max - min)) * width);

		KeyHandler h;
		h.on(keyCode::left, [&]() {cursor--; });
		h.on(keyCode::right, [&]() {cursor++;});
		h.on(keyCode::esc, [&]() {h.stop(); });
		h.on(keyCode::bspc, [&]() {h.stop(); });
		h.on(keyCode::enter, [&]() {
			*value = (int)(min + (max - min) * (cursor * step));
		});
		h.on(h.update, [&](){
			cls();
			for (int b = 0; b < (int)(width * 0.125); b++) {
					cout << ' ';
				}
			for (int i = 0; i < width; i++) {
				cout << (i == cursor ? 178 : '-');
			}
		});
		h.start();
	}
};

class FOption : public Option {
public:
	float* value;
	float min;
	float max;
	FOption(string a_name, float a_value, float min, float max) {
		type = VType::Flt;
		name = a_name;
		value = new float(a_value);
	}
	~FOption() {
		delete value;
		value = nullptr;
	}
	void* Value() {
		return value;
	}
	string draw() {
		return name + ": " + to_string(*value);
	}
	void write(stringstream& buffer) {
		buffer.write((const char*)(value), sizeof(float));
	}
	void read(stringstream& buffer) {
		buffer.clear();
		char data[5];
		buffer.get(data, 5);
		memcpy(value, data, 4);
	}
	void configure() {}
};

class BOption : public Option {
public:
	bool* value;
	BOption(string a_name, float a_value) {
		type = VType::Bll;
		name = a_name;
		value = new bool(a_value);
	}
	BOption(char* data[]) {

	}
	~BOption() {
		delete value;
		value = nullptr;
	}
	void* Value() {
		return value;
	}
	string draw() {
		return name + ": " + (*value ? "true" : "false");

	}
	void write(stringstream& buffer) {
		buffer.write((const char*)(value), sizeof(boolean));
		//buffer << *value;
	}
	void read(stringstream& buffer) {
		buffer.clear();
		char data[2];
		buffer.get(data, 2);
		memcpy(value, data, 1);
	}
	void configure(){
		*value = !*value;
	}
};

class OptionData {
public:
	vector<Option*> fields = {
		new SOption("StringTest", "test7", {"test", "tets1", "test2", "test3"}),
		new IOption("IntTest", 9, 0, 100),
		new FOption("FloatTest", 7.5f, 0.0f, 100.0f),
		new BOption("BooleanTest", true),
		new IOption("FieldSize", 3, 2, 10),
		new SOption("Speed", "medium", {"fast", "medium", "slow"})
	};
	Option* get(string s) {
      		for (Option* field : fields) {
			if (field->name == s)return field;
		}
		return nullptr;
	}
	~OptionData() {
		for (auto i : fields) {
			delete i;
		}
	}
};

class Settings : public BaseStructure, public OptionData {
	FileIO file;
	Menu menu;
public:
	void start();
	void init();
	void load();
	void save();
	void draw() {
		Menu m;
		//for (Option *o : fields) {
		for(int i = 0; i < fields.size(); i++){
			auto& o = fields[i];
			m.addField({[&]() {return o->draw(); }, [&]() {o->configure(); } });
		}
		m.addField({ "Save Settings", [&]() {save();  cls(); cout << "Saved"; Sleep(2000); } });
		m.start(false);
	}
};
/*

Game{
	Setting s;
	int* Volume = s.get("Volume").init();
}

*/