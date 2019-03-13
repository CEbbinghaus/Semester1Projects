#pragma once
#include"Rendering.h"
#include "Game.h"

using namespace std;

void GameRender::start() {}
void GameRender::init(){
	renderingField.clear();
 	int maxlength = (*game).maxGridSize;
	if (maxlength <= 0)return;
	while (renderingField.size() < maxlength) {
		vector<char> tmp;
		for (int i = 0; i < maxlength; i++) {
			tmp.push_back(0);
		}
		renderingField.push_back(tmp);
	}
}

string GameRender::playingFieldText(string prePendString) {
	std::string log = "";
	int localSize = *game->gridSize;// gridSize;
	int maxSize = (*game).maxGridSize;
	for (int x = 0; x < maxSize; x++) {
		for (int y = 0; y < maxSize; y++) {
			renderingField[x][y] = ' ';//254
			bool isWall = (x == 0 || x == maxSize - 1 || y == 0 || y == maxSize - 1);
			bool isSeperator = isWall ? false : (x % (1 + localSize) == 0 || y % (1 + localSize) == 0);
			bool isCenter = isWall ? false : ((2 + x) % (1 + localSize) == 0 && (2 + y) % (1 + localSize) == 0);
			if (isWall || isSeperator) {
				renderingField[x][y] = 'W';
				continue;
			}
			if (isCenter) {
				char tile = (*game).playingField[(x + 2) / (localSize + 1) - 1][(y + 2) / (localSize + 1) - 1];
				int fx = ((x + 2) / (localSize + 1) - 1);
				int fy = ((y + 2) / (localSize + 1) - 1);
				bool isCursor = ((*game).cursor['x'] == fx && (*game).cursor['y'] == fy);
				bool isTile = !(tile == ' ');
				renderingField[x][y] = isTile ? isCursor ? 176 : tile : (!isCursor ? ' ' : 219);
			}
		}
	}
	vector<vector<char>> drawField(renderingField);
	for (int x = 0; x < maxSize; x++) {
		for (int y = 0; y < maxSize; y++) {
			string tile = getPositionString(maxSize, x, y);
			drawField[x][y] = (tile != "") ? tiles[tile] : renderingField[x][y];
			//cout << tile << endl;
		}
		bool isSeperator = (x % (1 + localSize) == 0);
		log += prePendString + joinArray(drawField[x], isSeperator ? tiles["UD"] : ' ') + "\n";
	}
	return log;
}
void GameRender::draw() {
	cls();
	string tabs = "		";
	cout << endl << endl << endl;
	cout << playingFieldText(tabs) << endl << endl;
	cout << tabs + (*game).outputMessage << endl;
}
string GameRender::joinArray(vector<char> arr, char spacer) {
	string result = "";
	for (int i : arr) {
		result += i;
		result += spacer;
	}
	return result.substr(0, result.length() - 1);
}

string GameRender::getPositionString(int size, int x, int y) {
	string positionString = "";
	if (renderingField[x][y] != 'W')return positionString;
	if (!(y == 0) && renderingField[x][y - 1] == 'W')positionString += "U";
	if (!(y == size - 1) && renderingField[x][y + 1] == 'W')positionString += "D";
	if (!(x == 0) && renderingField[x - 1][y] == 'W')positionString += "L";
	if (!(x == size - 1) && renderingField[x + 1][y] == 'W')positionString += "R";
	return positionString;
}