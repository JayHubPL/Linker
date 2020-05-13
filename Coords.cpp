#include "Coords.h"

int Coords::getDirection() const {
	return direction;
}

int Coords::getX() const {
	return x;
}

int Coords::getY() const {
	return y;
}

void Coords::makeGap() {
	gap = true;
}

bool Coords::isGap() const {
	return gap;
}

int Coords::getType() const {
	if (x % 2 == 0 && y % 2 == 0) return 0; // vertex
	else if (x % 2 == 0 && y % 2 == 1) return 1; // vertival line
	else return 2; // horizontal line
}

bool Coords::operator< (const Coords &p) const {
	if (this->getX() == p.getX())
		return this->getY() < p.getY();
	else
		return this->getX() < p.getX();
};