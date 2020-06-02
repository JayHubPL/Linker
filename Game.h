#pragma once
#include "Level.h"
#include "Player.h"
#include "UI.h"

class Game {
	Level level;
	Player player;
	UI ui;
public:
	void gameLoop();
	void setupLevel(int);
	bool checkSolution();
	void saveProgress(int);
	void clearSave(int&, int&);
	int readSave();
};