#pragma once
#include <vector>
#include "Coords.h"
class Level;

class Player {
	std::vector<Coords> vMoveHistory;
public:
	friend class UI;
	int facing() const;
	Coords currPos() const;
	bool isVisited(const Coords&) const;
	bool move(int, Level&);
	void resetPlayer(const Coords&);
	Player(Coords pos = Coords(-1,-1,-1)) { vMoveHistory.push_back(pos); }
};