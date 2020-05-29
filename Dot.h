#pragma once
#include "LogicElement.h"

class Dot :public LogicElement {
public:
	void drawLogElem(cv::Mat&, int, std::pair<int, int>) override;
	bool isFulfilled(Player&, Level&) override;
	Dot(int x, int y) : LogicElement(Coords(x, y)) { }
};