#include <iostream>
#include "board.h"
#include "block.h"
#include <sstream>
using namespace std;

Board::Board(int numrow, int numcol, bool textOnly): level(0), score(0), hiscore(0), blocknum(0), gameend(false) {
	if (!textOnly) {
		xw = new Xwindow();
	}
	init(numrow, numcol);
	this->textOnly = textOnly;
}

Board::~Board() {
	/*for(int i; i < row; i++) {
     for(int j; j < col;j++) {
     delete grid[i][j];
     }
     }*/
    delete current;
    delete next;
    for(int i = 0;i < row;i++){
	    delete [] grid[i];
    }
    delete []grid;
    delete xw;
}

void Board::init(int numrow, int numcol) {
    row = numrow;
    col = numcol;
	grid = new Cell*[row];
	for(int i = 0; i < row; i++) {
		grid[i] = new Cell[col];
		for(int j = 0; j < col; j++) {
			grid[i][j] = Cell(j, i, xw);
		}
	}
}

void Board::genBlock(char type1, char type2) {
	current = new Block(type1, this, level);
	current->genBlock();
	next = new Block(type2, this, level);
}

void Board::left(int t) {
	if (current->legalmove("left", t)) {
		for (int i = 0; i < t; i++) {
			current->left();
		}
	}
}

void Board::right(int t) {
	if (current->legalmove("right", t)) {
		for (int i = 0; i < t; i++) {
			current->right();
		}
	}
}

void Board::down(int t) {
	if (current->legalmove("down", t)) {
		for (int i = 0; i < t; i++) {
			current->down();
		}
	}
}

void Board::rotate(int t, string direct) {
	if (current->legalmove(direct, t)) {
		for (int i = 0; i < t; i++) {
			current->rotate(direct);
		}
	}
}

void Board::drop(char type) {
	while(current->legalmove("down", 1)) {
		current->down();
	}
	for (int i = 0; i < 4; i++) {
		grid[current->getBlocky(i)][current->getBlockx(i)].blockindex = blocknum;
	}
	blocklevel[blocknum] = current->level;
	cellexist[blocknum] = 4;
	blocknum++;
	for (int i = 0; i < 4; i++) {
		if (current->getBlocky(i) < 4) {
			gameend = true;
			gameover();
		}
	}
	gen();
	if (!gameend) {
		current = next;
 		clearRow();
		current->genBlock();
		next = new Block(type, this,level);
	}
}

void Board::gen() {
	if (next->type == 'I') {
		if ((grid[3][0].status) || (grid[3][1].status) || (grid[3][2].status) || (grid[3][3].status)) {
			gameend = true;
		}
	} else if ((next->type == 'J') || (next->type == 'L')) {
		if ((grid[4][0].status) || (grid[4][1].status) || (grid[4][2].status)) {
			gameend = true;
		}
	} else if ((next->type == 'O') || (next->type == 'S')) {
		if ((grid[4][0].status) || (grid[4][1].status)) {
			gameend = true;
		}
	} else if (next->type == 'Z') {
		if ((grid[4][1].status) || (grid[4][2].status)) {
			gameend = true;
		}
	} else if (next->type == 'T') {
		if (grid[4][1].status) {
			gameend = true;
		}
	}
	if(gameend) {
		gameover();
	}
}

bool Board::checkfull(int r) {
    for(int a = 0; a < 10; a++) {
        if(grid[r][a].status == false) {
            return false;
        }
    }
    return true;
}

void Board::clearRow() {
	int numRows = 0;
    for(int a = 3; a < 18; a++) {
        if(checkfull(a)) {
			numRows++;
			for (int b = 0; b < 10; b++) {
				cellexist[grid[a][b].blockindex]--;
				if (cellexist[grid[a][b].blockindex] == 0) {
					score = score + (blocklevel[grid[a][b].blockindex] + 1) * (blocklevel[grid[a][b].blockindex] + 1);
					if (score > hiscore) {
						hiscore = score;
					}
				}
			}
			for (int a = 0; a < blocknum; a++) {
				if (cellexist[a] == 0) {
					for (int i = 0; i < 18; i++) {
						for (int j = 0; j < 10; j++) {
							if ((grid[i][j].blockindex != 150) && (grid[i][j].blockindex > a)) {
								grid[i][j].blockindex--;
							}
						}
					}
					for (int b = a; b < 150; b++) {
						blocklevel[b] = blocklevel[b + 1];
						cellexist[b] = cellexist[b + 1];
					}
					blocknum--;
				}
			}
            for (int i = a; i >= 3; --i) {
				for (int j = 0; j < 10; j++) {
                    grid[i][j].type = grid[i-1][j].type;
                    grid[i][j].status = grid[i-1][j].status;
					grid[i][j].blockindex = grid[i - 1][j].blockindex;
                }
            }
        }
    }
	if(numRows > 0) {
	    score = score + (level + numRows) * (level + numRows);
	}
	if (score > hiscore) {
		hiscore = score;
	}
}

ostream& operator<<(ostream &out, const Board &b) {
    cout << "Level:     " << b.level << endl;
	cout << "Score:     " << b.score << endl;
	cout << "Hi Score:  " << b.hiscore << endl;
	cout << "----------" << endl;
	for(int i = 0; i < b.row; i++) {
		for(int j = 0; j < b.col;j++) {
			cout << b.grid[i][j];
			
		}
		cout << i << endl;
	}
	cout << "----------" << endl;
	cout << "Next:" << endl;
	if (b.next->type == 'O') {
		cout << "OO" << endl;
		cout << "OO" << endl;
	} else if (b.next->type == 'I') {
		cout << "IIII" << endl;
	} else if (b.next->type == 'J') {
		cout << "J" << endl;
		cout << "JJJ" << endl;
	} else if (b.next->type == 'L') {
		cout << "  L" << endl;
		cout << "LLL" << endl;
	} else if (b.next->type == 'S') {
		cout << " SS" << endl;
		cout << "SS" << endl;
	} else if (b.next->type == 'Z') {
		cout << "ZZ" << endl;
		cout << " ZZ" << endl;
	} else if (b.next->type == 'T') {
		cout << "TTT" << endl;
		cout << " T " << endl;
	}
    return out;
}

void Board::gameover() {
	cout << "Game Over!" << endl;
	cout << "Score: " << score << endl;
	cout << "Hi Score: " << hiscore << endl;
	if(!textOnly) {
		string scorestr;
		ostringstream converts;
		converts << score;
		scorestr = converts.str();
		
		string histr;
		ostringstream converth;
		converth << hiscore;
		histr = converth.str();
		
		xw->drawBigString(75,250,"Game Over!",1);
		xw->drawBigString(75,300,"Score: " + scorestr, 1);
		xw->drawBigString(75,350, "Hi Score:  " + histr, 1);
	}
}

void Board::drawBoard() {
	string levelstr;
	ostringstream convertl;
	convertl << level;
	levelstr = convertl.str();
	
	string scorestr;
	ostringstream converts;
	converts << score;
	scorestr = converts.str();
	
	string histr;
	ostringstream converth;
	converth << hiscore;
	histr = converth.str();
	
    xw->fillRectangle(0,0,261,555,1);
    xw->fillRectangle(0,559,261,4,2);
    xw->fillRectangle(0,563,261,62,1);
    xw->fillRectangle(0,625,261,4,2);
    xw->fillRectangle(0,86,261,4,2);
    
    xw->drawBigString(0, 20, "Level:      " + levelstr, 0);
	xw->drawBigString(0, 40, "Score:      " + scorestr, 0);
	xw->drawBigString(0, 60, "Hi Score:  " + histr, 0);
	
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col;j++) {
			if(grid[i][j].status) {
		    	grid[i][j].drawCell();
		    } else {
		    	grid[i][j].undrawCell();
		    }
		}
	}
    
    xw->fillRectangle(1, 92 , 261, 1, 1);
	xw->fillRectangle(260, 92 , 1, 469, 1);
	xw->fillRectangle(0, 559, 261, 1, 1);
	xw->drawBigString(0, 585 , "Next: ", 0);
    
	if (next->type == 'O') {
		xw->fillRectangle(75, 565, 24, 24, 6);
		xw->fillRectangle(75, 590, 24, 24, 6);
		xw->fillRectangle(100, 565, 24, 24,6);
		xw->fillRectangle(100, 590, 24, 24,6);
	} else if (next->type == 'I') {
		xw->fillRectangle(75,  565, 24, 24, 3);
		xw->fillRectangle(100, 565, 24, 24, 3);
		xw->fillRectangle(125, 565, 24, 24, 3);
		xw->fillRectangle(150, 565, 24, 24, 3);
	} else if (next->type == 'J') {
		xw->fillRectangle(75, 565, 24, 24, 4);
		xw->fillRectangle(75, 590, 24, 24, 4);
		xw->fillRectangle(100, 590, 24, 24, 4);
		xw->fillRectangle(125, 590, 24, 24, 4);
	} else if (next->type == 'L') {
		xw->fillRectangle(125, 565, 24, 24, 5);
		xw->fillRectangle(75, 590, 24, 24, 5);
		xw->fillRectangle(100, 590, 24, 24, 5);
		xw->fillRectangle(125, 590, 24, 24, 5);
	} else if (next->type == 'S') {
		xw->fillRectangle(75, 590, 24, 24, 7);
		xw->fillRectangle(100, 565, 24, 24, 7);
		xw->fillRectangle(100, 590, 24, 24, 7);
		xw->fillRectangle(125, 565, 24, 24, 7);
	} else if (next->type == 'Z') {
		xw->fillRectangle(75, 565, 24, 24, 9);
		xw->fillRectangle(100, 565, 24, 24, 9);
		xw->fillRectangle(100, 590, 24, 24, 9);
		xw->fillRectangle(125, 590, 24, 24, 9);
	} else if (next->type == 'T') {
		xw->fillRectangle(75, 565, 24, 24, 8);
		xw->fillRectangle(100, 565, 24, 24, 8);
		xw->fillRectangle(100, 590, 24, 24, 8);
		xw->fillRectangle(125, 565, 24, 24, 8);
	}
}

void Board::skip(char type) {
	for (int i = 0; i < 4; i++) {
		grid[current->getBlocky(i)][current->getBlockx(i)].status = false;
	}
	if (!gameend) {
		current = next;
 		current->genBlock();
		next = new Block(type, this, level);
	}
}







