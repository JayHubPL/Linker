#pragma once
#include "opencv2/opencv.hpp"
#include "Player.h"
#include "Level.h"
#include "Coords.h"
#include "ColorPalette.h"

bool checkForPointInVector(const Coords&, const std::vector<Coords>&);
std::vector<Coords> findUnion(const Coords&, const Player&, const Level&);

class LogicElement :public Coords {
protected:
	LogicElement(Coords pos = Coords(-1, -1, -1)) : Coords(pos) { }
public:
	virtual void drawLogElem(cv::Mat&, int, std::pair<int, int>) = 0;
	virtual bool isFulfilled(Player&, Level&) = 0;
};