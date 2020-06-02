#include <string>
#include <algorithm>
#include "LogicElement.h"
#include "UI.h"

enum KEY {
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	Z = 122,
	X = 120,
	ESC = 27,
	ENTER = 13,
	NO_KEY = -1
};

enum MENU_STATUS {
	NEUTRAL = 0,
	NEW_GAME = 1,
	CONTINUE = 2,
	CREDITS_SELECT = 3,
	EXIT = 4,
	CREDITS = 5,
	ENDING= 6
};

void UI::initialize() {
	cv::namedWindow(winName);
	frame = cv::Mat::zeros(winHeight, winWidth, CV_8UC3);
}

int UI::navigateMenu(int key, bool& inMenu, bool& isRunning, bool& enterFlag, bool& ending) {
	static int menuStatus = NEUTRAL;
	if (ending)
		menuStatus = ENDING;
	if (menuStatus == NEUTRAL && key != -1)
		menuStatus = NEW_GAME;
	else if (menuStatus == CREDITS && key != -1)
		menuStatus = CREDITS_SELECT;
	else if (menuStatus == ENDING && key != -1) {
		menuStatus = NEUTRAL;
		ending = false;
	}
	else {
		switch (key) {
		case W:
			if (menuStatus > NEW_GAME)
				menuStatus = static_cast<MENU_STATUS>(static_cast<int>(menuStatus) - 1);
			break;
		case S:
			if (menuStatus < EXIT)
				menuStatus = static_cast<MENU_STATUS>(static_cast<int>(menuStatus) + 1);
			break;
		case ENTER:
			enterFlag = false;
			switch (menuStatus) {
			case NEUTRAL:
				menuStatus = NEW_GAME;
				break;
			case NEW_GAME:
				inMenu = false;
				return 0;
			case CONTINUE:
				inMenu = false;
				return 1;
			case CREDITS_SELECT:
				menuStatus = CREDITS;
				break;
			case EXIT:
				isRunning = false;
				break;
			}
			break;
		}
	}
	frame = cv::imread("menu/" + std::to_string(menuStatus) + ".png");
	return -1;
}

std::pair<int, int> UI::calculateOffset(const Level& lvl) {
	int w = 0, h = 0;
	for (int i = 0; i < lvl.tileCount(); i++) {
		w = std::max(w, lvl.getTile(i).getX());
		h = std::max(h, lvl.getTile(i).getY());
	}
	return { winWidth / 2 - ((w + 1) / 2) * scale, winHeight / 2 - ((h + 1) / 2) * scale };
}

void UI::drawLevel(Level &lvl, Player &player) {
	const int lineWidth = 6;
	const int ioRadius = 10;
	const std::pair<int, int> offset = calculateOffset(lvl);
	frame = cv::Mat::Mat(winHeight, winWidth, CV_8UC3, backgroundColor);
	// panel
	for (int i = 0; i < lvl.vPanel.size(); i++) {
		switch (lvl.vPanel[i].getType()) {
		case 0:
			cv::circle(frame,
				cv::Point(lvl.vPanel[i].getX() * scale + offset.first, lvl.vPanel[i].getY() * scale + offset.second),
				lineWidth / 2,
				ColorPalette::WHITE,
				-1);
			break;
		case 1:
			if (!lvl.vPanel[i].isGap())
				cv::rectangle(frame,
					cv::Point(lvl.vPanel[i].getX() * scale + offset.first - lineWidth / 2, lvl.vPanel[i].getY() * scale + offset.second - scale),
					cv::Point(lvl.vPanel[i].getX() * scale + offset.first + lineWidth / 2, lvl.vPanel[i].getY() * scale + offset.second + scale),
					ColorPalette::WHITE,
					-1);
			else {
				cv::rectangle(frame,
					cv::Point(lvl.vPanel[i].getX() * scale + offset.first - lineWidth / 2, lvl.vPanel[i].getY() * scale + offset.second - scale),
					cv::Point(lvl.vPanel[i].getX() * scale + offset.first + lineWidth / 2, lvl.vPanel[i].getY() * scale + offset.second - scale / 3),
					ColorPalette::WHITE,
					-1);
				cv::rectangle(frame,
					cv::Point(lvl.vPanel[i].getX() * scale + offset.first - lineWidth / 2, lvl.vPanel[i].getY() * scale + offset.second + scale / 3),
					cv::Point(lvl.vPanel[i].getX() * scale + offset.first + lineWidth / 2, lvl.vPanel[i].getY() * scale + offset.second + scale),
					ColorPalette::WHITE,
					-1);
			}
			break;
		case 2:
			if(!lvl.vPanel[i].isGap())
				cv::rectangle(frame,
					cv::Point(lvl.vPanel[i].getX() * scale + offset.first - scale, lvl.vPanel[i].getY() * scale + offset.second - lineWidth / 2),
					cv::Point(lvl.vPanel[i].getX() * scale + offset.first + scale, lvl.vPanel[i].getY() * scale + offset.second + lineWidth / 2),
					ColorPalette::WHITE,
					-1);
			else {
				cv::rectangle(frame,
					cv::Point(lvl.vPanel[i].getX() * scale + offset.first - scale, lvl.vPanel[i].getY() * scale + offset.second - lineWidth / 2),
					cv::Point(lvl.vPanel[i].getX() * scale + offset.first - scale / 3, lvl.vPanel[i].getY() * scale + offset.second + lineWidth / 2),
					ColorPalette::WHITE,
					-1);
				cv::rectangle(frame,
					cv::Point(lvl.vPanel[i].getX() * scale + offset.first + scale, lvl.vPanel[i].getY() * scale + offset.second - lineWidth / 2),
					cv::Point(lvl.vPanel[i].getX() * scale + offset.first + scale / 3, lvl.vPanel[i].getY() * scale + offset.second + lineWidth / 2),
					ColorPalette::WHITE,
					-1);
			}
			break;
		}
	}
	// logic elements
	for (int i = 0; i < lvl.vLogElem.size(); i++) {
		lvl.vLogElem[i]->drawLogElem(frame, scale, offset);
	}
	// entry circe
	cv::circle(frame,
		cv::Point(lvl.entry.getX() * scale + offset.first, lvl.entry.getY() * scale + offset.second),
		(int)(ioRadius * scale * .02),
		playerColor,
		-1);
	// exit circle
	cv::circle(frame,
		cv::Point(lvl.exit.getX() * scale + offset.first, lvl.exit.getY() * scale + offset.second),
		(int)(ioRadius * scale * .02),
		ColorPalette::WHITE,
		-1);
	// player's tracks
	for (int i = 1; i < player.vMoveHistory.size(); i++) {
		cv::circle(frame,
			cv::Point(player.vMoveHistory[i].getX() * scale + offset.first, player.vMoveHistory[i].getY() * scale + offset.second),
			lineWidth / 2,
			playerColor,
			-1);
		if (player.vMoveHistory[i].getDirection() == 119 || player.vMoveHistory[i].getDirection() == 115) {
			cv::rectangle(frame,
				cv::Point(player.vMoveHistory[i].getX() * scale + offset.first - lineWidth / 2, player.vMoveHistory[i].getY() * scale + offset.second),
				cv::Point(player.vMoveHistory[(int)i-1].getX() * scale + offset.first + lineWidth / 2, player.vMoveHistory[(int)i-1].getY() * scale + offset.second),
				playerColor,
				-1);
		}
		else {
			cv::rectangle(frame,
				cv::Point(player.vMoveHistory[i].getX() * scale + offset.first, player.vMoveHistory[i].getY() * scale + offset.second - lineWidth / 2),
				cv::Point(player.vMoveHistory[(int)i-1].getX() * scale + offset.first, player.vMoveHistory[(int)i-1].getY() * scale + offset.second + lineWidth / 2),
				playerColor,
				-1);
		}
	}
}

void UI::evaluateInput(int& key, bool& moveReq, bool& enterFlag, bool& inMenu) {
	switch (key) {
	case W:
	case A:
	case S:
	case D:
		if (!inMenu)
			moveReq = true;
		break;
	case ESC:
		inMenu = true;
		break;
	case ENTER:
		enterFlag = true;
		break;
	case Z:
	case X:
		break;
	default:
		key = NO_KEY;
		break;
	}
}

int UI::showFrame(int frameRate) const{
	cv::setWindowTitle(winName, winTitle);
	cv::imshow(winName, frame);
	return cv::waitKey(frameRate);
}

void UI::setTitle(const std::string title) {
	winTitle = title;
}
