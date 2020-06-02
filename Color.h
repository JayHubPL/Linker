#pragma once
#include "LogicElement.h"

class Color :public LogicElement {
	const int colorID;
public:
	bool isFulfilled(Player&, Level&) override;
	void drawLogElem(cv::Mat&, int, std::pair<int, int>) override;
	Color(int x, int y, int colorID) : LogicElement(Coords(x,y)), colorID(colorID) { }
};