#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>
#include <string>
#include "board.h"
#include "block.h"
#include "cell.h"

class Game {
	
private:
	Board* board;
	std::string scriptfile;
	bool textOnly;
	int startlevel;
	int filesize;
	int hiscore;
public:
	Game();
	~Game();
	void start();
	void end();
	void srtLevel(int n);
	void textonly();
	void setfile(std::string s);
	void restart();
	std::string readfile();
	char genlevelblock(int level);
};

#endif