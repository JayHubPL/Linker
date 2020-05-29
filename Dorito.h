#pragma once
#include "LogicElement.h"

class Dorito : public LogicElement {
	int count;
public:
	void drawLogElem(cv::Mat&, int, std::pair<int, int>) override;
	bool isFulfilled(Player&, Level&) override;
	Dorito(int x, int y, int count) : LogicElement(Coords(x, y)), count(count) { };
};

