#pragma once

#include<iostream>
#include <time.h>

#include"Settings.h"

using namespace std;

///--------------------------------SETTINGS
void Settings::start() {
	draw();
}
void Settings::init() {
	load();
}
void Settings::save() {
	//for loop through fields to get stringstream
	stringstream buffer;

	//Signed with Copyright and Current Date/Time
	buffer.write(copyright, sizeof(char) * copyrightSize);
	unsigned int t = 0;
	buffer.write((const char*)&t, sizeof(int));

	for (int i = 0; i < fields.size(); i++) {
		fields[i]->write(buffer);
	}

	if (file.write(buffer) && file.sign(copyrightSize, time(0))) {
		cout << "Successfully Saved" << endl;
	}
	else {
		cout << "Failed to Save. Try restarting the game with Administrator Permissions" << endl;
	}

	cout << "Output Called";
	return;
}

void Settings::load() {
	stringstream buffer;
	if (file.read(buffer)) {
		buffer.seekg(0, ios::beg);
		buffer.clear();

		char cpr[copyrightSize];
		buffer.get(cpr, copyrightSize, '\0');
		buffer.seekg(1, ios::cur);

		if (strcmp(cpr, copyright) != 0){
			cls();
			cout << "INVALID DATA SIGNATURE";
			_sleep(2000);
			exit(0);
		}
		cout << "DATA VERIFIED";
		_sleep(200);

		unsigned int date = 999999;
		char data[sizeof(int) + 1];
		buffer.get(data, sizeof(int) + 1);
 		memcpy(&date, data, sizeof(int));

		buffer.clear();
		for (int i = 0; i < fields.size(); i++) {
			fields[i]->read(buffer);
		}
	}
	else {
		cls();
		cout << "Failed to Load Settings" << endl;
		Sleep(200);
		cout << "Saving to File" << endl;
		save();
		Sleep(2000);
	}
}


void Settings::draw() {
	Menu m;
	//for (Option *o : fields) {
	for (int i = 0; i < fields.size(); i++) {
		auto& o = fields[i];
		m.addField({ [&]() {return o->draw(); }, [&]() {o->configure(); } });
	}
	m.addField({ "Save Settings", [&]() {save();  cls(); cout << "Saved"; Sleep(2000); } });
	m.start(false);
}
///------------------------------------------------------OptionData

OptionData::~OptionData() {
	for (auto i : fields) {
		delete i;
	}
}

Option* OptionData::get(string s) {
	for (Option* field : fields) {
		if (field->name == s)return field;
	}
	return nullptr;
}

///------------------------------------------------------Options
//-----------------------IOption
IOption::IOption(string a_name, int a_value, int a_min, int a_max) {
	type = VType::Int;
	name = a_name;
	value = new int(a_value);
	min = a_min;
	max = a_max;
}

IOption::~IOption() {
	delete value;
	value = nullptr;
}

void* IOption::Value() {
	return value;
}

void IOption::write(stringstream& buffer) {
	buffer.write((const char*)(value), sizeof(int));
}

void IOption::read(stringstream& buffer) {
	buffer.clear();
	char data[5];
	buffer.get(data, 5);
	memcpy(value, data, 4);
}

string IOption::draw() {
	return name + ": " + to_string(*value);

}

void IOption::configure() {
	int width = (int)(ConsoleWidth() / 0.75);
	float step = 1 / width;
	int cursor = floor(((*value - min) / (max - min)) * width);

	KeyHandler h;
	h.on(keyCode::left, [&]() {cursor--; });
	h.on(keyCode::right, [&]() {cursor++; });
	h.on(keyCode::esc, [&]() {h.stop(); });
	h.on(keyCode::bspc, [&]() {h.stop(); });
	h.on(keyCode::enter, [&]() {
		*value = (int)(min + (max - min) * (cursor * step));
		h.stop();
	});
	h.on(h.update, [&]() {
		cls();
		for (int b = 0; b < (int)(width * 0.125); b++) {
			cout << ' ';
		}
		for (int i = 0; i < width; i++) {
			cout << (char)((i == cursor) ? 178 : '-');
		}
	});
	h.start();
}

//----------------------FOption

FOption::FOption(string a_name, float a_value, float a_min, float a_max) {
	type = VType::Flt;
	name = a_name;
	value = new float(a_value);
	min = a_min;
	max = a_max;
}

FOption::~FOption() {
	delete value;
	value = nullptr;
}

void* FOption::Value() {
	return value;
}

void FOption::read(stringstream& buffer) {
	buffer.clear();
	char data[5];
	buffer.get(data, 5);
	memcpy(value, data, 4);
}

void FOption::write(stringstream& buffer) {
	buffer.write((const char*)(value), sizeof(float));
}

string FOption::draw() {
	return name + ": " + to_string(*value);
}

void FOption::configure() {}

//-----------------------SOption

SOption::SOption(string a_name, const char* a_value, vector<string> options) {
	type = VType::Str;
	name = a_name;
	possibilities = options;
	value = new char[32];
	strcpy(value, a_value);
}

SOption::~SOption() {
	delete value;
	value = nullptr;
}

void* SOption::Value() {
	return value;
}

void SOption::write(stringstream& buffer) {
	buffer << value;
	buffer << '\0';
}

void SOption::read(stringstream& buffer) {
	buffer.clear();
	buffer.get(value, 32, '\0');
	buffer.seekg(1, ios::cur);
	cout << value;
}

string SOption::draw() {
	return name + ": " + value;
}

void SOption::configure() {
	Menu m;
	for (string s : possibilities) {
		m.addField({ s, [=]() {strcpy(value, s.c_str()); } });
	}

	auto currentValue = find(possibilities.begin(), possibilities.end(), string(value));
	if (currentValue != possibilities.end())
		m.setCursor(distance(possibilities.begin(), currentValue));
	m.draw();
	Sleep(200);
	m.start();
}

//----------------------BOption

BOption::BOption(string a_name, float a_value) {
	type = VType::Bll;
	name = a_name;
	value = new bool(a_value);
}

BOption::~BOption() {
	delete value;
	value = nullptr;
}

void* BOption::Value() {
	return value;
}

string BOption::draw() {
	return name + ": " + (*value ? "true" : "false");

}

void BOption::write(stringstream& buffer) {
	buffer.write((const char*)(value), sizeof(boolean));
	//buffer << *value;
}

void BOption::read(stringstream& buffer) {
	buffer.clear();
	char data[2];
	buffer.get(data, 2);
	memcpy(value, data, 1);
}

void BOption::configure() {
	*value = !*value;
}