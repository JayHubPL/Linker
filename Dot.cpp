#include "Dot.h"

void Dot::drawLogElem(cv::Mat &canvas, int scale, std::pair<int, int> offset) {
	const int dotRadius = 6;
	cv::circle(canvas,
		cv::Point(x * scale + offset.first, y * scale + offset.second),
		dotRadius,
		cv::Scalar(60, 40, 40),
		-1);
}

bool Dot::isFulfilled(Player &player, Level &lvl) {
	return player.isVisited(Coords(x, y));
}