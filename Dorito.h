#pragma once
#include "LogicElement.h"

// id 3

class Dorito : public LogicElement {
	int count;
public:
	void drawLogElem(cv::Mat&, int, std::pair<int, int>) override;
	bool isFulfilled(Player&, Level&) override;
	Dorito(int x, int y, int count) : LogicElement(Coords(x, y), 3), count(count) { };
};

