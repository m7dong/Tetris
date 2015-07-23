#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include <string>
#include "cell.h"
#include "window.h"

class Block;

class Board {
private:
	Block* current;
	Block* next;
	int row;
	int col;
	int blocknum;
	int blocklevel[151];
	int cellexist[151];
	bool textOnly;
public:
	bool gameend;
	Xwindow *xw;
	int level, score, hiscore;
	Cell** grid;
	Board(int r, int c, bool textonly);
	~Board();
	void init(int r, int c);
	void genBlock(char type1, char type2);
	void left(int t = 1);
	void right(int t = 1);
	void down(int t = 1);
	void rotate(int t = 1, std::string direct = "clockwise");
	void drop(char type);
	void gen();
	friend std::ostream& operator<<(std::ostream &out, const Board &b);
    bool checkfull(int r);
	void clearRow();
	void drawBoard();
	void gameover();
	void skip(char type);
};

#endif