#pragma once

#include<iostream>


#include"Settings.h"

using namespace std;

void Settings::start() {
	draw();
}
void Settings::init() {
	load();
}
void Settings::save() {
	//for loop through fields to get stringstream
	stringstream buffer;

	//TODO: Sign with Copyright and Date

	for (int i = 0; i < fields.size(); i++) {
		fields[i]->write(buffer);
	}

	if (file.write(buffer)) {
		cout << "Successfully Saved" << endl;
	}
	else {
		cout << "Failed to Save. Try restarting the game with Administrator Permissions" << endl;
	}
	//TTTCEbbinghaus19

	cout << "Output Called";
	//stringstream s;
	//for (Option* i : D.fields) {
	//	i->toBString(&s);
	//}
	//output << s.str().c_str();
	return;
}
//Settings* Settings::addOption(Option o) {
//	this->options.push_back(o);
//	return this;
//}

void Settings::load() {
	stringstream buffer;
	if (file.read(buffer)) {
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