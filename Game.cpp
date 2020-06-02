#include <fstream>
#include "LogicElement.h"
#include "Game.h"

std::ostream& operator<< (std::ostream& os, const std::vector<Coords>& v) {
	os << v.size() << " ";
	for (std::vector<Coords>::const_iterator i = v.begin(); i != v.end(); ++i)
		os << (*i).getX() << " " << (*i).getY() << " " << (*i).getDirection() << " ";
	os << '\n';
	return os;
}

void goToLine(std::fstream& file, const int line) {
	file.seekg(std::ios::beg);
	for (int i = 0; i < line - 1; ++i)
		file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Game::clearSave(int &lastSolved, int &currLvl) {
	lastSolved = -1;
	currLvl = 0;
	std::fstream file;
	file.open("save.txt", std::ios::out);
	file << "";
	file.close();
}

void Game::setupLevel(int lvlNo) {
	level.readLevelData(lvlNo);
	player.resetPlayer(level.getEntry());
	std::fstream file;
	file.open("save.txt", std::ios::in);
	goToLine(file, 2 * lvlNo + 2);
	int vSize = 0;
	if (file >> vSize) {
		int param1 = 0, param2 = 0, param3 = 0;
		std::vector<Coords> savedMoves;
		for (int i = 0; i < vSize; i++) {
			file >> param1 >> param2 >> param3;
			savedMoves.push_back(Coords(param1, param2, param3));
		}
		player.setMoveHistory(savedMoves);
	}
	file.close();
	ui.setTitle("Linker: Level " + std::to_string(lvlNo));
}

bool Game::checkSolution() {
	if (player.currPos() != level.getExit())
		return false;
	level.resetLogElemData();
	for (int i = 0; i < level.logElemCount(); i++)
		if (!level.getLogElem(i)->isFulfilled(player, level))
			return false;
	return true;
}

void Game::saveProgress(int lvlNo) {
	std::fstream file;
	file.open("save.txt", std::ios::app);
	file << lvlNo << '\n';
	file << player.getMoveHistory();
	file.close();
}

int Game::readSave() {
	std::fstream file;
	int lvlNo = -1;
	file.open("save.txt", std::ios::in);
	for (int i = 1; file.good(); i += 2) {
		goToLine(file, i);
		file >> lvlNo;
	}
	file.close();
	return lvlNo;
}

void Game::gameLoop() {
	// last level #
	const int lastLvlNo = 65;
	// level and save data
	int lastSolved = readSave();
	int currLvl = (lastSolved + 1) % lastLvlNo; // overflow protection
	// flags
	int pressedKey = -1;
	bool isRunning = true;
	bool inMenu = true;
	bool moveReq = false;
	bool enterFlag = false;
	bool ending = false;
	// main loop
	while (isRunning) {
		// menu
		if (inMenu) {
			ui.setTitle("Linker");
			switch (ui.navigateMenu(pressedKey, inMenu, isRunning, enterFlag, ending)) {
			case 0: // new game
				clearSave(lastSolved, currLvl);
			case 1: // continue
				setupLevel(currLvl);
				break;
			}
		}
		// gameplay
		else {
			// checking solution and progression
			if (enterFlag) {
				if (checkSolution()) {
					// was it unbeaten level
					if (currLvl == lastSolved + 1) {
						saveProgress(currLvl);
						lastSolved++;
					}
					// was it the last level
					if (lastSolved == lastLvlNo) {
						ending = true;
						inMenu = true;
					}
					// not the last level
					else {
						setupLevel(++currLvl);
					}
				}
				// wrong answer / reset
				else {
					player.resetPlayer(level.getEntry());
				}
				enterFlag = false;
			}
			// player tries to move
			else if (moveReq) {
				player.move(pressedKey, level);
				moveReq = false;
			}
			// level scrolling
			if (pressedKey == 'z' && currLvl > 0)
				setupLevel(--currLvl);
			else if (pressedKey == 'x' && currLvl < lastLvlNo && currLvl <= lastSolved)
				setupLevel(++currLvl);
			// draw level frame
			ui.drawLevel(level, player);
		}
		// show frame and capture valid input
		pressedKey = ui.showFrame(1);
		ui.evaluateInput(pressedKey, moveReq, enterFlag, inMenu);
	}
}