#pragma once
#include "Level.h"
#include "Player.h"
#include "UI.h"

class Game {
public:
	Level level;
	Player player;
	UI ui;
	void gameLoop();
	void setupLevel(int);
	bool checkSolution();
	void saveProgress(int);
	int readSave();
};