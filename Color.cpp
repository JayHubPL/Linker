#include "Color.h"

bool Color::isFulfilled(Player& player, Level& lvl) {
	int keyID = -1;
	std::vector<Coords> vInUnion = findUnion(Coords(x, y), player, lvl);
	for (int i = 0; i < vInUnion.size(); i++) {
		for (int k = 0; k < lvl.logElemCount(); k++)
			if (vInUnion[i] == *(lvl.getLogElem(k)) && lvl.getLogElem(k)->getID() == 1) {
				if (keyID == -1)
					keyID = (std::static_pointer_cast<Color>(lvl.getLogElem(k)))->colorID;
				else if (keyID != (std::static_pointer_cast<Color>(lvl.getLogElem(k)))->colorID)
					return false;
			}
	}
	return true;
}

void Color::drawLogElem(cv::Mat& canvas, int scale, std::pair<int, int> offset) {
	cv::Scalar color;
	switch (colorID) {
	case 0:
		color = cv::Scalar(240, 207, 137);
		break;
	case 1:
		color = cv::Scalar(100, 220, 80);
		break;
	case 2:
		color = cv::Scalar(197, 246, 253);
		break;
	}
	cv::rectangle(canvas,
		cv::Point(x * scale + offset.first - scale / 10, y * scale + offset.second - scale / 5),
		cv::Point(x * scale + offset.first + scale / 10, y * scale + offset.second + scale / 5),
		color,
		-1);
	cv::rectangle(canvas,
		cv::Point(x * scale + offset.first - scale / 5, y * scale + offset.second - scale / 10),
		cv::Point(x * scale + offset.first + scale / 5, y * scale + offset.second + scale / 10),
		color,
		-1);
	// TODO: too much code here for 4 circles
	cv::circle(canvas,
		cv::Point(x * scale + offset.first - scale / 10, y * scale + offset.second - scale / 10),
		scale / 10,
		color,
		-1);
	cv::circle(canvas,
		cv::Point(x * scale + offset.first - scale / 10, y * scale + offset.second + scale / 10),
		scale / 10,
		color,
		-1);
	cv::circle(canvas,
		cv::Point(x * scale + offset.first + scale / 10, y * scale + offset.second - scale / 10),
		scale / 10,
		color,
		-1);
	cv::circle(canvas,
		cv::Point(x * scale + offset.first + scale / 10, y * scale + offset.second + scale / 10),
		scale / 10,
		color,
		-1);
}