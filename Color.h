#pragma once
#include "LogicElement.h"

class Color :public LogicElement {
	const int colorID;
public:
	bool isFulfilled(Player&, Level&);
	virtual void drawLogElem(cv::Mat&, int, std::pair<int, int>);
	Color(int x, int y, int colorID) : LogicElement(Coords(x,y)), colorID(colorID) { }
};