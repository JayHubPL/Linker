#pragma once
#include <vector>
#include <memory>
#include "Coords.h"
class LogicElement;

class Level {
	Coords entry, exit;
	std::vector<Coords> vPanel;
	std::vector<Coords> vTile;
	std::vector<std::shared_ptr<LogicElement>> vLogElem;
public:
	friend class UI;
	friend class Player;
	Coords getEntry() const;
	Coords getExit() const;
	bool checkForPoint(const Coords&) const;
	bool checkForTile(const Coords&) const;
	void resetLogElemData();
	size_t logElemCount() const;
	size_t tileCount() const;
	std::shared_ptr<LogicElement> getLogElem(int) const;
	Coords getTile(int) const;
	void clearLevelData();
	void readLevelData(int);
};