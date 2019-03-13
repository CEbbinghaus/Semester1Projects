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
	SOption(string a_name, const char* a_value, vector<string> options);
	~SOption();
	void* Value();
	void write(stringstream& buffer);
	void read(stringstream& buffer);
	string draw();;
	void configure();
};

class IOption : public Option {
public:
	int* value;
	int min;
	int max;
	IOption(string a_name, int a_value, int a_min, int a_max);
	~IOption();
	void* Value();
	void write(stringstream& buffer);
	void read(stringstream& buffer);
	string draw();
	void configure();
};

class FOption : public Option {
public:
	float* value;
	float min;
	float max;
	FOption(string a_name, float a_value, float min, float max);
	~FOption();
	void* Value();
	string draw();
	void write(stringstream& buffer);
	void read(stringstream& buffer);
	void configure();
};

class BOption : public Option {
public:
	bool* value;
	BOption(string a_name, float a_value);
	~BOption();
	void* Value();
	string draw();
	void write(stringstream& buffer);
	void read(stringstream& buffer);
	void configure();
};

class OptionData {
public:
	vector<Option*> fields = {
		new SOption("StringTest", "test7", {"test", "tets1", "test2", "test3"}),
		new IOption("IntTest", 9, 0, 100),
		new FOption("FloatTest", 7.5f, 0.0f, 100.0f),
		new BOption("BooleanTest", true),
		new IOption("FieldSize", 3, 2, 10),
		new SOption("Speed", "medium", {"fast", "medium", "slow"}),
		new SOption("Speed", "medium", {"fast", "medium", "slow"})
	};


	~OptionData();
	Option* get(string s);
};

class Settings : public BaseStructure, public OptionData {
	static const unsigned int copyrightSize = 48;
	const char copyright[copyrightSize] = {"Copyright Christopher-Robin Ebbinghaus, 3132019"};
	FileIO file;
	Menu menu;
public:
	void start();
	void init();
	void load();
	void save();
	void draw();
};
/*

Game{
	Setting s;
	int* Volume = s.get("Volume").init();
}

*/