#include "cell.h"
#include <iostream>
using namespace std;

Cell::Cell() {}

Cell::Cell(int x, int y, Xwindow* w): status(false), x(x), y(y), blockindex(150), xw(w) {}

/*Cell::Cell (Cell &other) {
 x = other.x;
 y = other.y;
 level = other.level;
 type = other.type;
 }*/

Cell::~Cell() {
}

int Cell:: getX() {
	return x;
}

int Cell::getY() {
	return y;
}

int Cell::getLevel() {
	return level;
}

char Cell::getType() {
	return type;
}

void Cell::setType(char c) {
	type = c;
}

void Cell::drawCell() {
	if (type == 'I') {
		xw->fillRectangle(x * 25 + x + 1, y * 25 + 93 + y, 25, 25, 3);
	} else if (type == 'J') {
		xw->fillRectangle(x * 25 + x + 1, y * 25 + 93 + y, 25, 25, 4);
	} else if (type == 'L') {
		xw->fillRectangle(x * 25 + x + 1, y * 25 + 93 + y, 25, 25, 5);
	} else if (type == 'O') {
		xw->fillRectangle(x * 25 + x + 1, y * 25 + 93 + y, 25, 25, 6);
	} else if (type == 'S') {
		xw->fillRectangle(x * 25 + x + 1, y * 25 + 93 + y, 25, 25, 7);
	} else if (type == 'T') {
		xw->fillRectangle(x * 25 + x + 1, y * 25 + 93 + y, 25, 25, 8);
	} else if (type == 'Z') {
		xw->fillRectangle(x * 25 + x + 1, y * 25 + 93 + y, 25, 25, 9);
	}
}

void Cell::undrawCell() {
	xw->fillRectangle(x * 25 + x + 1, y * 25 + 93 + y, 25, 25, 1);
}

ostream& operator<<(ostream &out, Cell &cell) {
    if (cell.status) {
        out << cell.type;
    } else {
        out << " ";
    }
    return out;
}
