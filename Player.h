#pragma once
#include <vector>
#include "Coords.h"
class Level;

class Player {
	std::vector<Coords> vMoveHistory;
public:
	friend class UI;

	const std::vector<Coords>& getMoveHistory() const;
	void setMoveHistory(std::vector<Coords>&);

	int facing() const;
	Coords currPos() const;
	bool isVisited(const Coords&) const;
	bool move(int, Level&);
	void resetPlayer(const Coords&);
	Player(Coords pos = Coords(-1,-1,-1)) { vMoveHistory.push_back(pos); }
};