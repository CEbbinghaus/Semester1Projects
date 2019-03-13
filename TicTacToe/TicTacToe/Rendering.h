#pragma once
#include<string>
#include <map>
#include <vector>

#include "Scaffold.h"

using namespace std;

class Game;

class GameRender : BaseStructure{
public:
	map<string, char> tiles =
	{
		{"UDL", 202},  //T-Intersection Left -|
		{"UDR", 203},  //T-Intersection Right |-
		{"ULR", 185},  //T-Intersection Top _|_
		{"DLR", 204},  //T-Intersection Bottom ⁻|⁻
		{"LR", 186},  //Straight Vertical |
		{"UD", 205},  //Straight Horizontal _
		{"DL", 200}, //LCorner Bottom Left ⁻|
		{"UL", 188}, //LCorner Top Left _|
		{"UR", 187}, //LCorner Top Right |_
		{"DR", 201}, //LCorner Bottom Right |⁻
		{"UDLR", 206}    //X Intersection -|-
	};
	vector<vector<char>> renderingField;
	Game* game;
	GameRender(Game *a_game) {
		game = a_game;
	};
	void start();
	void init();
	void draw();
	string joinArray(vector<char> arr, char spacer = 0);
	string playingFieldText(string prePendString);
	string getPositionString(int size, int x, int y);
};