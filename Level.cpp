#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "LogicElement.h"
#include "Dot.h"
#include "Color.h"
#include "Level.h"
#include "Tetromino.h"
#include "Dorito.h"

Coords Level::getEntry() const {
	return entry;
}

Coords Level::getExit() const {
	return exit;
}

bool Level::checkForPoint(const Coords &p) const {
	return checkForPointInVector(p, vPanel);
}

bool Level::checkForTile(const Coords& p) const {
	return checkForPointInVector(p, vTile);
}

size_t Level::logElemCount() const {
	return vLogElem.size();
}

size_t Level::tileCount() const {
	return vTile.size();
}

Coords Level::getTile(int i) const {
	return vTile[i];
}

std::shared_ptr<LogicElement> Level::getLogElem(int i) const {
	return vLogElem[i];
}

void Level::clearLevelData() {
	entry = Coords();
	exit = Coords();
	vPanel.clear();
	vTile.clear();
	vLogElem.clear();
}

void Level::readLevelData(int lvlNo) {
	clearLevelData();
	std::fstream file;
	file.open("levels/" + std::to_string(lvlNo) + ".txt", std::ios::in);
	std::string input;
	int x, y, param1, param2, stage = -1;
	const std::vector<std::pair<int, int>> vShift = { {0, -1}, {0, 1}, {-1, 0}, {1, 0}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1} };
	const std::vector<std::string> vLabel = { "$TILE", "$ENTRY", "$EXIT", "$DOT", "$COLOR", "$TETROMINO", "$GAP", "$DORITO" };
	const std::vector<std::string> vTemplate = { "#2x2", "#2x3", "#3x2", "#3x3", "#3x4", "#4x3", "#4x4", "#4x5", "#5x4", "#5x5" };
	while (file >> input) {
		if (input[0] == '$') {
			for (int i = 0; i < vLabel.size(); i++)
				if (input == vLabel[i])
					stage = i;
			continue;
		}
		if (input[0] == '#') {
			for (int k = 0; k < vTemplate.size(); k++)
				if (input == vTemplate[k]) {
					for (int n = 1; n <= 2 * (vTemplate[k][3] - '0') - 1; n += 2)
						for (int m = 1; m <= 2 * (vTemplate[k][1] - '0') - 1; m += 2) {
							vTile.push_back(Coords(m, n));
							for (int i = 0; i < vShift.size(); i++)
								if (!checkForPoint(Coords(m + vShift[i].first, n + vShift[i].second)))
									vPanel.push_back(Coords(m + vShift[i].first, n + vShift[i].second));
						}
					entry = Coords(0, 2 * (vTemplate[k][3] - '0'));
					exit = Coords(2 * (vTemplate[k][1] - '0'), 0);
				}
			continue;
		}
		x = std::stoi(input);
		file >> y;
		switch (stage) {
		case 0:
			vTile.push_back(Coords(x, y));
			for (int i = 0; i < vShift.size(); i++)
				if (!checkForPoint(Coords(x + vShift[i].first, y + vShift[i].second)))
					vPanel.push_back(Coords(x + vShift[i].first, y + vShift[i].second));
			break;
		case 1:
			entry = Coords(x, y);
			break;
		case 2:
			exit = Coords(x, y);
			break;
		case 3:
			vLogElem.emplace_back(new Dot(x, y));
			break;
		case 4:
			file >> param1;
			vLogElem.emplace_back(new Color(x, y, param1));
			break;
		case 5:
			file >> param1 >> param2;
			vLogElem.emplace_back(new Tetromino(x, y, param1, param2));
			break;
		case 6:
			for (int i = 0; i < vPanel.size(); i++)
				if (vPanel[i] == Coords(x, y))
					vPanel[i].makeGap();
			break;
		case 7:
			file >> param1;
			vLogElem.emplace_back(new Dorito(x, y, param1));
			break;
		}
	}
	file.close();
}