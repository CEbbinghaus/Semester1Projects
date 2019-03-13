#pragma once
#include <iostream>
#include"Game.h"

using namespace std;

Game::Game(Settings* options) {
	render = new GameRender(this);
	settings = options; 
	gridSize = (int*)settings->get("FieldSize")->Value();
	maxGridSize = (*gridSize * *gridSize) + (*gridSize + 1);
	init();
}

void Game::start() {
	currentPlayer = state::cross;
	clearPlayingField();
	outputMessage = playerTitles[currentPlayer] + messages["input"];
	update();
	handler.start();
}
void Game::genPlayingField() {
	Deconstruct();
	playingField = new int*[*gridSize];
	for (int i = 0; i < *gridSize; ++i)
	{
		playingField[i] = new int[*gridSize];
	}
}

void Game::init() {
	genPlayingField();
	clearPlayingField();

	//Setting up the Key Handler Inputs
	handler.on(keyCode::up, [&]() {cursor['x']--; });
	handler.on(keyCode::down, [&]() {cursor['x']++; });
	handler.on(keyCode::left, [&]() {cursor['y']--; });
	handler.on(keyCode::right, [&]() {cursor['y']++; });
	handler.on(keyCode::space, [&]() {tick(); });
	handler.on(keyCode::enter, [&]() {tick(); });
	handler.on(handler.update, [&]() {update(); });
	render->init();
}
void Game::clearPlayingField() {
	cursor['x'] = cursor['y'] = 0;
	for (int x = 0; x < *gridSize; x++) {
		for (int y = 0; y < *gridSize; y++) {
			playingField[x][y] = undefined;
		}
	}
}
void Game::tick() {
	int* field = &playingField[cursor['x']][cursor['y']];
	if (*field != state::undefined) {
		outputMessage = messages["taken"];
		return;
	}
	*field = currentPlayer;
	if (hasWon()) {
		cls();
		cout << playerTitles[currentPlayer] << " Has Won";
		handler.stop();
	}
	currentPlayer = currentPlayer == state::circle ? state::cross : state::circle;
	outputMessage = playerTitles[currentPlayer] + messages["input"];
}
void Game::update() {
	clamp<int>(cursor['x'], 0, *gridSize - 1);
	clamp<int>(cursor['y'], 0, *gridSize - 1);
	draw();
}
bool Game::hasWon() {
	if (isWinner()) {
		draw();
		system("pause");
		return true;
	}
	if (isFilled()) {
		draw();
		system("pause");
		return true;
	}
	return false;
}
bool Game::isFilled() {
	bool result = true;
	for (int x = 0; x < *gridSize; x++) {
		for (int y = 0; y < *gridSize; y++) {
			result = playingField[x][y] == undefined ? false : result;
		}
	}
	if (result)outputMessage = "The Game ends in a Draw";
	return result;
}
bool Game::isWinner() {
	int winCount = *gridSize;
	int DR = 0;
	int DL = 0;
	for (int x = 0; x < *gridSize; x++) {
		char FDR = playingField[x][x];
		DR += FDR == undefined ? 0 : FDR == circle ? 1 : -1;

		char FDL = playingField[(*gridSize - 1) - x][x];
		DL += FDL == undefined ? 0 : FDL == circle ? 1 : -1;


		int xs = 0;
		int ys = 0;
		for (int y = 0; y < *gridSize; y++) {
			xs += playingField[x][y] == undefined ? 0 : playingField[x][y] == circle ? 1 : -1;
			ys += playingField[y][x] == undefined ? 0 : playingField[y][x] == circle ? 1 : -1;
		}
		bool PlayerOneWon = (xs == winCount || ys == winCount || DR == winCount || DL == winCount);
		bool PlayerTwoWon = (xs == -winCount || ys == -winCount || DR == -winCount || DL == -winCount);
		if (PlayerOneWon || PlayerTwoWon) {
			outputMessage = playerTitles[currentPlayer] + " Wins";
			return true;

		}
	}
	return false;
}
void Game::Deconstruct() {
}
Game::~Game() {
	Deconstruct();
}
void Game::draw() {
	render->draw();
}