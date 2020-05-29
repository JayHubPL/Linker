#include "Dorito.h"

bool Dorito::isFulfilled(Player& player, Level& lvl) {
	const std::vector<std::pair<int, int>> vShift = { {0,1}, {1,0}, {0,-1}, {-1,0} };
	int ctr = 0;
	for (int i = 0; i < 4; i++)
		if (player.isVisited(Coords(x + vShift[i].first, y + vShift[i].second)))
			ctr++;
	return (ctr == count);
}

void Dorito::drawLogElem(cv::Mat& canvas, int scale, std::pair<int, int> offset) {
	const int size = 16;
	cv::Point triangle[3];
	triangle[0] = cv::Point(x * scale + offset.first - size / 2, y * scale + offset.second - (int)(size * .29));
	triangle[1] = cv::Point(x * scale + offset.first + size / 2, y * scale + offset.second - (int)(size * .29));
	triangle[2] = cv::Point(x * scale + offset.first, y * scale + offset.second + (int)(size * .58));
	if (count == 1)
		cv::fillConvexPoly(canvas, triangle, 3, ColorPalette::WHITE);
	else if (count == 2) {
		for (int i = 0; i < 3; i++)
			triangle[i] -= cv::Point((int)(size * .7), 0);
		cv::fillConvexPoly(canvas, triangle, 3, ColorPalette::WHITE);
		for (int i = 0; i < 3; i++)
			triangle[i] += cv::Point((int)(size * 1.4), 0);
		cv::fillConvexPoly(canvas, triangle, 3, ColorPalette::WHITE);
	}
	else if (count == 3) {
		cv::fillConvexPoly(canvas, triangle, 3, ColorPalette::WHITE);
		for (int i = 0; i < 3; i++)
			triangle[i] -= cv::Point((int)(size * 1.3), 0);
		cv::fillConvexPoly(canvas, triangle, 3, ColorPalette::WHITE);
		for (int i = 0; i < 3; i++)
			triangle[i] += cv::Point((int)(size * 2.6), 0);
		cv::fillConvexPoly(canvas, triangle, 3, ColorPalette::WHITE);
	}
		
}