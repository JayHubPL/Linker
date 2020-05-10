#include <stack>
#include "LogicElement.h"

bool checkForPointInVector(const Coords& p, const std::vector<Coords>& v) {
	for (int i = 0; i < v.size(); i++)
		if (p == v[i])
			return true;
	return false;
}

std::vector<Coords> findUnion(const Coords& start, const Player& player, const Level& lvl) {
	std::stack<Coords> s;
	std::vector<Coords> vInUnion;
	const std::vector<std::pair<int, int>> vShift = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };
	s.push(start);
	vInUnion.push_back(start);
	while (!s.empty()) {
		Coords tmp = s.top();
		s.pop();
		for (int i = 0; i < 4; i++) {
			Coords checkedTile = Coords(tmp.getX() + 2 * vShift[i].first, tmp.getY() + 2 * vShift[i].second);
			if (!player.isVisited(Coords(tmp.getX() + vShift[i].first, tmp.getY() + vShift[i].second)) && lvl.checkForTile(checkedTile)) {
				if (!checkForPointInVector(checkedTile, vInUnion)) {
					vInUnion.push_back(checkedTile);
					s.push(Coords(checkedTile));
				}
			}
		}
	}
	return vInUnion;
}