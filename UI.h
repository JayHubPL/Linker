#pragma once
#include <string>
#include "opencv2/opencv.hpp"
#include "Level.h"
#include "Player.h"
#include "ColorPalette.h"

class UI {
	cv::Mat frame;
	const cv::String winName;
	cv::String winTitle;
	const int winWidth;
	const int winHeight;
public:
	const int scale;
	const cv::Scalar backgroundColor;
	const cv::Scalar playerColor;
	void initialize();
	int navigateMenu(int, bool&, bool&, bool&, bool&);
	void drawLevel(Level&, Player&);
	int showFrame(int, int) const;
	void setTitle(const std::string);
	void evaluateInput(int&, bool&, bool&, bool&);
	std::pair<int, int> calculateOffset(const Level&);
	UI() : winName("Linker"), winTitle("Linker"), winWidth(550), winHeight(550), scale(50), backgroundColor(ColorPalette::YELLOW), playerColor(ColorPalette::GREY) { initialize(); }
};