#include "Tetromino.h"

void Tetromino::drawLogElem(cv::Mat& canvas, int scale, std::pair<int, int> offset) {
	static const int spread = 8;
	static const int size = 6;
	cv::Scalar color;
	if (rotatable)
		color = cv::Scalar(60, 20, 220);
	else
		color = cv::Scalar(255, 255, 255);
	int w = 0, h = 0;
	for (int i = 0; i < shape.size(); i++) {
		w = std::max(w, 2 * shape[i].first);
		h = std::max(h, 2 * shape[i].second);
	}
	w /= 2;
	h /= 2;
	for (int i = 0; i < shape.size(); i++)
		cv::rectangle(canvas,
			cv::Point(x * scale + offset.first + (2 * shape[i].first - w) * spread - size, y * scale + offset.second + (2 * shape[i].second - h) * spread - size),
			cv::Point(x * scale + offset.first + (2 * shape[i].first - w) * spread + size, y * scale + offset.second + (2 * shape[i].second - h) * spread + size),
			color,
			-1);
}

class BaseXNum {
	int digit[50];
	int length; // max 49
	int base;
public:
	bool increment() {
		digit[0]++;
		for (int i = 0; i < length; i++)
			if (digit[i] == base) {
				digit[i] = 0;
				digit[i + 1]++;
			}
		if (digit[length] == 1)
			return false;
		return true;
	}
	int getDigit(int pos) const {
		return digit[pos];
	}
	BaseXNum(int length, int x) : length(length), base(x) {
		for (int i = 0; i <= length; i++)
			digit[i] = 0;
	}
};

void rotatePoint(std::pair<int, int>& p, int k) {
	for (int i = 0; i < k; i++) {
		std::swap(p.first, p.second);
		p.second *= -1;
	}
}

bool Tetromino::isFulfilled(Player& player, Level& lvl) {
	// checking if union resolver previously
	if (inSolution)
		return true;
	std::vector<Coords> vTilesInUnion = findUnion(Coords(x, y), player, lvl);
	std::vector<std::vector<std::pair<int, int>>> vTetrominosInUnion;
	std::vector<bool> rotatability;
	// storing pointers for inSolution update
	std::vector<std::shared_ptr<LogicElement>> vPtr;
	for (int i = 0; i < vTilesInUnion.size(); i++)
		for (int k = 0; k < lvl.logElemCount(); k++)
			if (vTilesInUnion[i] == *(lvl.getLogElem(k)) && lvl.getLogElem(k)->getID() == 2) {
				vPtr.push_back(lvl.getLogElem(k));
				vTetrominosInUnion.push_back((std::static_pointer_cast<Tetromino>(lvl.getLogElem(k)))->shape);
				rotatability.push_back((std::static_pointer_cast<Tetromino>(lvl.getLogElem(k)))->rotatable);
			}
	BaseXNum rotation((int)vTetrominosInUnion.size(), 4);
	size_t sumOfTiles = 0;
	for (int i = 0; i < vTetrominosInUnion.size(); i++) {
		sumOfTiles += vTetrominosInUnion[i].size();
	}
	if (sumOfTiles != vTilesInUnion.size())
		return false;
	std::sort(vTilesInUnion.begin(), vTilesInUnion.end());
	std::vector<Coords> occupied;
	do {
		// rotation generator
		std::vector<std::vector<std::pair<int, int>>> vTetros = vTetrominosInUnion;
		for (int i = 0; i < vTetros.size(); i++)
			if (rotatability[i])
				for (int k = 1; k < vTetros[i].size(); k++) // first point should always be (0, 0) so no need for rotating it: "int k = 1"
					rotatePoint(vTetros[i][k], rotation.getDigit(i));
		BaseXNum placement((int)vTetros.size(), (int)vTilesInUnion.size());
		do {
			// placement generator
			for (int i = 0; i < vTetros.size(); i++)
				for (int k = 0; k < vTetros[i].size(); k++)
					occupied.push_back(Coords(2 * vTetros[i][k].first + vTilesInUnion[placement.getDigit(i)].getX(), 2 * vTetros[i][k].second + vTilesInUnion[placement.getDigit(i)].getY()));
			std::sort(occupied.begin(), occupied.end());
			bool correct = true;
			for (int i = 0; i < vTilesInUnion.size(); i++)
				if (occupied[i] != vTilesInUnion[i]) {
					correct = false;
					break;
				}
			if (correct) {
				for (int i = 0; i < vPtr.size(); i++)
					(std::static_pointer_cast<Tetromino>(vPtr[i]))->inSolution = true;
				return true;
			}
			occupied.clear();
		} while (placement.increment());
	} while (rotation.increment());
	return false;
}

Tetromino::Tetromino(int x, int y, int shapeID, bool rotatable) : LogicElement(Coords(x, y), 2), rotatable(rotatable), inSolution(false) {
	static const std::vector<std::vector<std::pair<int, int>>> vAllShapes = {
		{ {0,0} },
		{ {0,0},{0,1} },
		{ {0,0},{0,1},{1,0},{1,1} },
		{ {0,0},{0,1},{0,2} },
		{ {0,0},{0,1},{0,2},{0,3} },
		{ {0,0},{1,0},{0,1},{0,2} },
		{ {0,0},{1,0},{1,1},{1,2} },
		{ {0,0},{0,1},{1,1} },
		{ {0,0},{1,1} },
		{ {0,0},{1,0},{2,0},{1,1} }
	};
	shape = vAllShapes[shapeID];
}


