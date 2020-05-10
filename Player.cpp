#include "Player.h"
#include "Level.h"

int Player::facing() const {
	return this->vMoveHistory.back().getDirection();
}

void Player::resetPlayer(const Coords& pos) {
	vMoveHistory.clear();
	vMoveHistory.push_back(pos);
}

Coords Player::currPos() const {
	return vMoveHistory.back();
}

bool Player::isVisited(const Coords &pos) const {
	for (int i = 0; i < vMoveHistory.size(); i++)
		if (pos == vMoveHistory[i])
			return true;
	return false;
}

bool Player::move(int dir, Level &lvl) {
	static const std::vector<int> vDir = { 119, 97, 115, 100 };
	int vecDirPos;
	for (int i = 0; i < 4; i++)
		if (dir == vDir[i]) {
			vecDirPos = i;
			if (facing() == vDir[(vecDirPos + 2) % 4]) {
				vMoveHistory.pop_back();
				return true;
			}
		}
	static const std::vector<std::pair<int, int>> vShift = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };
	Coords newPos = Coords(currPos().getX() + vShift[vecDirPos].first, currPos().getY() + vShift[vecDirPos].second, dir);
	if (lvl.checkForPoint(newPos)) {
		for (int i = 0; i < lvl.vPanel.size(); i++)
			if (newPos == lvl.vPanel[i] && lvl.vPanel[i].isGap())
				return false;
		for (int i = 0; i < vMoveHistory.size(); i++)
			if (newPos == vMoveHistory[i])
				return false;
		vMoveHistory.push_back(newPos);
		return true;
	}
	return false;
}