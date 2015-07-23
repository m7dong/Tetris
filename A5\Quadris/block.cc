#include <iostream>
#include "block.h"
using namespace std;

Block::Block(char type, Board* board, int lvl): numExist(4), type(type), board(board), tracex(1), tracey(3), legal(true) {
	level = lvl;
}

Block::Block(Block &other) {
	numExist = other.numExist;
	type = other.type;
	board = other.board;
	tracex = other.tracex;
	tracey = other.tracey;
}

Block::~Block() {
}

void Block::drawIBlock() {
	blockx[0] = 0;
	blocky[0] = 3;
	board->grid[3][0].status = true;
	board->grid[3][0].setType('I');
	blockx[1] = 1;
	blocky[1] = 3;
	board->grid[3][1].status = true;
	board->grid[3][1].setType('I');
	blockx[2] = 2;
	blocky[2] = 3;
	board->grid[3][2].status = true;
	board->grid[3][2].setType('I');
	blockx[3] = 3;
	blocky[3] = 3;
	board->grid[3][3].status = true;
	board->grid[3][3].setType('I');
	tracex = 1;
	tracey = 3;
	type = 'I';
}

void Block::drawJBlock() {
	blockx[0] = 0;
	blocky[0] = 3;
	board->grid[3][0].status = true;
	board->grid[3][0].setType('J');
	blockx[1] = 0;
	blocky[1] = 4;
	board->grid[4][0].status = true;
	board->grid[4][0].setType('J');
	blockx[2] = 1;
	blocky[2] = 4;
	board->grid[4][1].status = true;
	board->grid[4][1].setType('J');
	blockx[3] = 2;
	blocky[3] = 4;
	board->grid[4][2].status = true;
	board->grid[4][2].setType('J');
	tracex = 1;
	tracey = 3;
	type = 'J';
}

void Block::drawLBlock() {
	blockx[0] = 2;
	blocky[0] = 3;
	board->grid[3][2].status = true;
	board->grid[3][2].setType('L');
	blockx[1] = 0;
	blocky[1] = 4;
	board->grid[4][0].status = true;
	board->grid[4][0].setType('L');
	blockx[2] = 1;
	blocky[2] = 4;
	board->grid[4][1].status = true;
	board->grid[4][1].setType('L');
	blockx[3] = 2;
	blocky[3] = 4;
	board->grid[4][2].status = true;
	board->grid[4][2].setType('L');
	tracex = 1;
	tracey = 3;
	type = 'L';
}

void Block::drawOBlock() {
	blockx[0] = 0;
	blocky[0] = 3;
	board->grid[3][0].status = true;
	board->grid[3][0].setType('O');
	blockx[1] = 1;
	blocky[1] = 3;
	board->grid[3][1].status = true;
	board->grid[3][1].setType('O');
	blockx[2] = 0;
	blocky[2] = 4;
	board->grid[4][0].status = true;
	board->grid[4][0].setType('O');
	blockx[3] = 1;
	blocky[3] = 4;
	board->grid[4][1].status = true;
	board->grid[4][1].setType('O');
	tracex = 1;
	tracey = 3;
	type = 'O';
}

void Block::drawSBlock() {
	blockx[0] = 1;
	blocky[0] = 3;
	board->grid[3][1].status = true;
	board->grid[3][1].setType('S');
	blockx[1] = 2;
	blocky[1] = 3;
	board->grid[3][2].status = true;
	board->grid[3][2].setType('S');
	blockx[2] = 0;
	blocky[2] = 4;
	board->grid[4][0].status = true;
	board->grid[4][0].setType('S');
	blockx[3] = 1;
	blocky[3] = 4;
	board->grid[4][1].status = true;
	board->grid[4][1].setType('S');
	tracex = 1;
	tracey = 3;
	type = 'S';
}

void Block::drawTBlock() {
	blockx[0] = 0;
	blocky[0] = 3;
	board->grid[3][0].status = true;
	board->grid[3][0].setType('T');
	blockx[1] = 1;
	blocky[1] = 3;
	board->grid[3][1].status = true;
	board->grid[3][1].setType('T');
	blockx[2] = 2;
	blocky[2] = 3;
	board->grid[3][2].status = true;
	board->grid[3][2].setType('T');
	blockx[3] = 1;
	blocky[3] = 4;
	board->grid[4][1].status = true;
	board->grid[4][1].setType('T');
	tracex = 1;
	tracey = 3;
	type = 'T';
}

void Block::drawZBlock() {
	blockx[0] = 0;
	blocky[0] = 3;
	board->grid[3][0].status = true;
	board->grid[3][0].setType('Z');
	blockx[1] = 1;
	blocky[1] = 3;
	board->grid[3][1].status = true;
	board->grid[3][1].setType('Z');
	blockx[2] = 1;
  	blocky[2] = 4;
	board->grid[4][1].status = true;
	board->grid[4][1].setType('Z');
	blockx[3] = 2;
	blocky[3] = 4;
	board->grid[4][2].status = true;
	board->grid[4][2].setType('Z');
	tracex = 1;
	tracey = 3;
	type = 'Z';
}

void Block::genBlock() {
	if (type == 'I') {
		drawIBlock();
	} else if (type == 'J') {
		drawJBlock();
	} else if (type == 'L') {
		drawLBlock();
	} else if (type == 'O') {
		drawOBlock();
	} else if (type == 'S') {
		drawSBlock();
	} else if (type == 'T') {
		drawTBlock();
	} else if (type == 'Z') {
		drawZBlock();
	}
}

bool Block::blockCleared() {
	if(numExist == 0) {
		return true;
	} else {
		return false;
	}
}

int Block::getTracex() {
	return tracex;
}

int Block::getTracey() {
	return tracey;
}

int Block::getBlockx(int x) {
	return blockx[x];
}

int Block::getBlocky(int y) {
	return blocky[y];
}

void Block::setBlockx(int i, int x) {
	blockx[i] = x;
}

void Block::setBlocky(int i, int y) {
	blocky[i] = y;
}

char Block::getType() {
	return type;
}

bool Block::legalmove(string command, int t) {
	legal = true;
	for (int i = 0; i < 4; i++) {
		board->grid[blocky[i]][blockx[i]].status = false;
	}
	if (command == "left") {
		for (int i = 0; i < t; i++) {
			for (int a = 0; a < 4; a++) {
				if (blockx[a] - 1 < 0) {
					legal = false;
				} else if (board->grid[blocky[a]][blockx[a] - 1].status ==  true) {
					legal = false;
				}
			}
		}
	}
	if (command == "right") {
		for (int i = 0; i < t; i++) {
			for (int a = 0; a < 4; a++) {
				if (blockx[a] + 1 > 9) {
					legal = false;
				} else if (board->grid[blocky[a]][blockx[a] + 1].status ==  true) {
					legal = false;
				}
			}
		}
	}
	if (command == "down") {
		for (int i = 0; i < t; i++) {
			for (int a = 0; a < 4; a++) {
				if (blocky[a] + 1 > 17) {
					legal = false;
				} else if (board->grid[blocky[a] + 1][blockx[a]].status ==  true) {
					legal = false;
				}
			}
		}
	}
	if (command == "clockwise") {
		if (type != 'I') {
			int x0 = tracex;
			int y0 = tracey;
			int xmin = blockx[0];
			int ymax = blocky[0];
			for (int i = 0; i < 4; i++) {
				if (blockx[i] < xmin) {
					xmin = blockx[i];
				}
				if (blocky[i] > ymax) {
					ymax = blocky[i];
				}
			}
			for (int a = 0; a < 4; a++) {
				int x = blockx[a];
				int y = blocky[a];
				x =  -(y - y0) + x0;
				y =  (x - x0) + y0;
				if ((x0 - xmin) != 1) {
					x--;
				}
				if ((ymax - y0) != 1) {
					y++;
				}
				if (x > 9 || x < 0) {
					legal = false;
				}
				if (y > 17 || y < 0) {
					for (int i = 0; i < 4; i++) {
						board->grid[blocky[i]][blockx[i]].status = true;
					}
					legal = false;
				}
				if(board->grid[y][x].status == true) {
					for (int i = 0; i < 4; i++) {
						board->grid[blocky[i]][blockx[i]].status = true;
					}
                    legal = false;
				}
			}
		} else if (type == 'I') {
			if (blockx[0] == blockx[1]) {
				if (blockx[0] > 6) {
					legal = false;
				}
			}
		}
    }
	if (command == "counterclockwise") {
		if (type != 'I') {
    		int x0 = tracex;
			int y0 = tracey;
			int xmin = blockx[0];
			int ymax = blocky[0];
			for (int i = 0; i < 4; i++) {
				if (blockx[i] < xmin) {
					xmin = blockx[i];
				}
				if (blocky[i] > ymax) {
					ymax = blocky[i];
				}
			}
			for (int a = 0; a < 4; a++) {
				int x = blockx[a];
				int y = blocky[a];
			    x = (y - y0) + x0;
				y = -(x - x0) + y0;
				if ((xmin - x0) == 1) {
					x--;
				}
				if ((ymax - y0) == 1) {
					y++;
				}
				if (x > 9 || x < 0) {
					legal = false;
				}
				if (y > 17 || y < 0) {
					legal = false;
				}
				if(board->grid[y][x].status == true) {
					legal = false;
				}
			}
		} else if (type == 'I') {
			if (blockx[0] == blockx[1]) {
				if (blockx[0] > 6) {
					legal = false;
				}
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		board->grid[blocky[i]][blockx[i]].status = true;
	}
	return legal;
}

void Block::left() {
	if(legalmove("left", 1)) {
		for(int a = 0; a < 4; a++) {
			board->grid[blocky[a]][blockx[a]].status = false;
			blockx[a] = blockx[a] - 1;
		}
		tracex--;
		for (int i = 0; i < 4; i++) {
			board->grid[blocky[i]][blockx[i]].status = true;
			board->grid[blocky[i]][blockx[i]].setType(type);
		}
	}
}

void Block::right() {
	if(legalmove("right", 1)) {
		for(int a = 0; a < 4; a++) {
			board->grid[blocky[a]][blockx[a]].status = false;
			blockx[a] = blockx[a] + 1;
		}
		tracex++;
		for (int i = 0; i < 4; i++) {
			board->grid[blocky[i]][blockx[i]].status = true;
			board->grid[blocky[i]][blockx[i]].setType(type);
		}
	}
}

void Block::down() {
	if(legalmove("down", 1)) {
		for(int a = 0; a < 4; a++) {
			board->grid[blocky[a]][blockx[a]].status = false;
			blocky[a] = blocky[a] + 1;
		}
		tracey++;
		for (int i = 0; i < 4; i++) {
			board->grid[blocky[i]][blockx[i]].status = true;
			board->grid[blocky[i]][blockx[i]].setType(type);
		}
	}
}


void Block::rotateClock() {
	if (legalmove("clockwise", 1)) {
		if (type != 'I') {
			for (int i = 0; i < 4; i++) {
				board->grid[blocky[i]][blockx[i]].status = false;
			}
			int x0 = tracex;
			int y0 = tracey;
			for (int i = 0; i < 4; i++) {
				int x = blockx[i];
				int y = blocky[i];
				blockx[i] = -(y - y0) + x0;
				blocky[i] = (x - x0) + y0;
			}
			leftbottom();
		} else if (type == 'I') {
			for(int i = 0; i<4 ;i++) {
				board->grid[blocky[i]][blockx[i]].status = false;
			}
			if (blockx[0] == blockx[1]) {
				int y = blocky[3];
                int x = blockx[3];
				for (int i = 0; i < 4; i++) {
					blockx[i] = x + i;
					blocky[i] = y;
				}
			} else if (blocky[0] == blocky[1]) {
				int x = blockx[0];
                int y = blocky[0];
				for (int i = 0; i < 4; i++) {
					blockx[i] = x;
					blocky[i] = y - (3 - i);
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			board->grid[blocky[i]][blockx[i]].status = true;
			board->grid[blocky[i]][blockx[i]].setType(type);
		}
	}
}

void Block::rotateCounter() {
	if (legalmove("counterclockwise", 1)) {
		if (type != 'I') {
			for (int i = 0; i < 4; i++) {
				board->grid[blocky[i]][blockx[i]].status = false;
			}
			int x0 = tracex;
			int y0 = tracey;
			for (int i = 0; i < 4; i++) {
				int x = blockx[i];
				int y = blocky[i];
				blockx[i] = (y - y0) + x0;
				blocky[i] = -(x - x0) + y0;
			}
			int xmin = blockx[0];
			int ymax = blocky[0];
			leftbottom();
		} else if (type == 'I') {
            for(int i = 0; i<4 ;i++) {
				board->grid[blocky[i]][blockx[i]].status = false;
			}
			if (blockx[0] == blockx[1]) {
				int y = blocky[3];
                int x = blockx[3];
				for (int i = 0; i < 4; i++) {
					blockx[i] = x + i;
					blocky[i] = y;
				}
			} else if (blocky[0] == blocky[1]) {
				int x = blockx[0];
                int y = blocky[0];
				for (int i = 0; i < 4; i++) {
					blockx[i] = x;
					blocky[i] = y - (3 - i);
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			board->grid[blocky[i]][blockx[i]].status = true;
			board->grid[blocky[i]][blockx[i]].setType(type);
		}
	}
}

void Block::rotate(string direct) {
	if (direct == "clockwise") {
		rotateClock();
	} else if (direct == "counterclockwise") {
		rotateCounter();
	}
}

void Block::leftbottom() {
	int x0 = tracex;
	int y0 = tracey;
	int xmin = blockx[0];
	int ymax = blocky[0];
	for (int i = 0; i < 4; i++) {
		if (blockx[i] < xmin) {
			xmin = blockx[i];
		}
		if (blocky[i] > ymax) {
			ymax = blocky[i];
		}
	}
	if (! ((x0 - xmin) == 1)) {
		for (int i = 0; i < 4; i++) {
			int x = blockx[i];
			blockx[i] = x - 1;
		}
	}
	if (! ((ymax - y0) == 1)) {
		for (int i = 0; i < 4; i++) {
			int y = blocky[i];
			blocky[i] = y + 1;
		}
	}
}











