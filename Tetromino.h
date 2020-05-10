#pragma once
#include "LogicElement.h"

// id 2

class Tetromino : public LogicElement {
	const bool rotatable;
	std::vector<std::pair<int, int>> shape;
	bool inSolution;
public:
	void drawLogElem(cv::Mat&, int, std::pair<int, int>) override;
	bool isFulfilled(Player&, Level&) override;
	Tetromino(int, int, int, bool);
};