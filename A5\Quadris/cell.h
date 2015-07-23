#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include "window.h"

class Cell {
private:
	int x;
	int y;
	Xwindow *xw;
public:
	int blockindex;
	int level;
	char type;
	bool status;
	Cell();
	Cell(int x, int y, Xwindow* xw);
	//Cell (Cell &other);
	~Cell();
	int getX();
	int getY();
	int getLevel();
	char getType();
	void setType(char c);
	
	void drawCell();
	void undrawCell();
	
	friend std::ostream& operator<<(std::ostream &out, Cell &c);
};

#endif
