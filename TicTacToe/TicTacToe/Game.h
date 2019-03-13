#pragma once
#include <map>
#include <vector>
#include "Scaffold.h"
#include "Settings.h"
#include "Rendering.h"
#include "util.h"

using namespace std;
class GameRenderer;

class Game: BaseStructure
{
	enum state
	{
		cross = 'X',
		circle = 'O',
		undefined = ' '
	};

	map<string, string> messages =
	{
		{"input", " Select a Field"},
		{"taken", "This Field Has Already Been Picked Please Pick Another One"}
	};

	map<int, char> stateIdentifiers =
	{
		{circle, 'O'},
		{cross, 'X'},
		{undefined, 0}
	};

	map<int, string> playerTitles =
	{
		{circle, "Circle"},
		{cross, "Cross"}
	};
	void Deconstruct();
public:
	int* gridSize;
	int maxGridSize;
	int** playingField;
	state currentPlayer = circle;
	string outputMessage;
	KeyHandler handler;
	GameRender* render;
	Settings* settings;

	map<char, int> cursor =
	{
		{'x', 0},
		{'y', 0}
	};
	Game(Settings* options);
	~Game();
	void genPlayingField();
	void clearPlayingField();
	void start();
	bool hasWon();
	void tick();
	void init();
	void update();
	bool isWinner(); 
	bool isFilled();
	void draw();
};