#ifndef __BLOCK_H__
#define __BLOCK_H__
#include <iostream>
#include "cell.h"
#include "board.h"

class Block {
private:
	Board* board;
	int blockx[4];
	int blocky[4];
	int numExist;
	int tracex;
	int tracey;
	bool legal;
public:
	int level;
	char type;
	Block(char type, Board* board, int lvl);
	Block(Block &other);
	~Block();
	void drawIBlock();
	void drawJBlock();
	void drawLBlock();
	void drawOBlock();
	void drawSBlock();
	void drawZBlock();
	void drawTBlock();
	void genBlock();
	bool blockCleared();
	void removeCell();
	int getTracex();
	int getTracey();
	int getBlockx(int x);
	int getBlocky(int y);
	void setBlockx(int i, int x);
	void setBlocky(int i, int y);
	char getType();
	
	bool legalmove(std::string command, int t);
	void left();
	void right();
	void down();
	void rotateClock();
	void rotateCounter();
	void rotate(std::string direct);
	void leftbottom();
};

#endif