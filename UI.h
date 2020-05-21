#pragma once
#include <string>
#include "opencv2/opencv.hpp"
#include "Level.h"
#include "Player.h"

class UI {
	cv::Mat frame;
	const std::string winName;
	const int winWidth;
	const int winHeight;
public:
	const int scale;
	const cv::Scalar backgroundColor;
	const cv::Scalar playerColor;
	void initialize();
	int navigateMenu(int, bool&, bool&, bool&, bool&);
	void drawLevel(Level&, Player&);
	int showFrame(int);
	void evaluateInput(int&, bool&, bool&, bool&);
	std::pair<int, int> calculateOffset(const Level&);
	UI() : winName("Linker"), winWidth(550), winHeight(550), scale(50), backgroundColor(cv::Scalar(0, 190, 255)), playerColor(cv::Scalar(133, 133, 133)) { initialize(); }
};