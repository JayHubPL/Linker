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
	triangle[0] = cv::Point(x * scale + offset.first - size / 2, y * scale + offset.second - size * .29);
	triangle[1] = cv::Point(x * scale + offset.first + size / 2, y * scale + offset.second - size * .29);
	triangle[2] = cv::Point(x * scale + offset.first, y * scale + offset.second + size * .58);
	if (count == 1)
		cv::fillConvexPoly(canvas, triangle, 3, cv::Scalar(255, 255, 255));
	else if (count == 2) {
		for (int i = 0; i < 3; i++)
			triangle[i] -= cv::Point(size * .6, 0);
		cv::fillConvexPoly(canvas, triangle, 3, cv::Scalar(255, 255, 255));
		for (int i = 0; i < 3; i++)
			triangle[i] += cv::Point(size * 1.2, 0);
		cv::fillConvexPoly(canvas, triangle, 3, cv::Scalar(255, 255, 255));
	}
	else if (count == 3) {
		cv::fillConvexPoly(canvas, triangle, 3, cv::Scalar(255, 255, 255));
		for (int i = 0; i < 3; i++)
			triangle[i] -= cv::Point(size * 1.1, 0);
		cv::fillConvexPoly(canvas, triangle, 3, cv::Scalar(255, 255, 255));
		for (int i = 0; i < 3; i++)
			triangle[i] += cv::Point(size * 2.2, 0);
		cv::fillConvexPoly(canvas, triangle, 3, cv::Scalar(255, 255, 255));
	}
		
}