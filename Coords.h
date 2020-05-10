#pragma once

class Coords {
protected:
	int x, y;
	int direction;
	bool gap;
public:
	int getDirection() const;
	int getX() const;
	int getY() const;
	void makeGap();
	bool isGap() const;
	int getType() const;
	bool operator== (const Coords &p) const { return (this->x == p.x && this->y == p.y); }
	bool operator!= (const Coords &p) const { return (this->x != p.x || this->y != p.y); }
	Coords(int x = -1, int y = -1, int dir = -1) : x(x), y(y), direction(dir), gap(false) { }
};