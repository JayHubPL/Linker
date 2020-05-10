#include <iostream>
#include <fstream>
#include "LogicElement.h"
#include "Game.h"

void Game::setupLevel(int lvlNo) {
	level.readLevelData(lvlNo);
	player.resetPlayer(level.getEntry());
	saveProgress(lvlNo);
}

bool Game::checkSolution() {
	if (player.currPos() != level.getExit())
		return false;
	for (int i = 0; i < level.logElemCount(); i++)
		if (!level.getLogElem(i)->isFulfilled(player, level))
			return false;
	return true;
}

void Game::saveProgress(int lvlNo) {
	std::fstream file;
	file.open("save.txt", std::ios::out);
	file << lvlNo;
	file.close();
}

int Game::readSave() {
	std::fstream file;
	int lvlNo = 0;
	file.open("save.txt", std::ios::in);
	file >> lvlNo;
	file.close();
	return lvlNo;
}

void Game::gameLoop() {

	int currLevel = readSave();
	int pressedKey = -1;
	bool isRunning = true;
	bool inMenu = true;
	bool moveReq = false;
	bool enterFlag = false;

	ui.initialize();

	while (isRunning) {
		if (inMenu) {
			switch (ui.navigateMenu(pressedKey, inMenu, isRunning, enterFlag)) {
			case 0:
				currLevel = 0;
				setupLevel(0);
				break;
			case 1:
				setupLevel(currLevel);
				break;
			}
			moveReq = false; // scraps after navigating menu
		}
		else { // for gameplay exclusively
			ui.drawLevel(level, player);
			if (enterFlag) {
				if (checkSolution()) {
					currLevel++;
					// overflow
					if (currLevel == 5)
						currLevel = 0;
					setupLevel(currLevel);
				}
				player.resetPlayer(level.getEntry());
				enterFlag = false;
			}
			else if (moveReq) {
				player.move(pressedKey, level);
				moveReq = false;
			}
		}
		pressedKey = ui.showFrame(1); // key press detection
		ui.evaluateInput(pressedKey, moveReq, enterFlag, inMenu); // could be removed
	}
	return;
}