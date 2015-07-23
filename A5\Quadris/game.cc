#include "game.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
using namespace std;

Game::Game() {
	board = NULL;
	scriptfile = "sequence.txt";
	textOnly = false;
	startlevel = 0;
	filesize = 0;
}

Game::~Game() {}

string Game::readfile() {
	ifstream fin(scriptfile.c_str());
	string s;
    
	while(fin >> s) {
		filesize++;
	}
	
    
	fin.close();
	fin.open(scriptfile.c_str());
	
    
	char sequence[filesize + 1];
	for (int i = 0; i < filesize; i++) {
		fin >> s;
    	sequence[i] = s[0];
	}
	sequence[filesize] = '\0';
	return sequence;
}

char Game::genlevelblock(int level) {
	int random;
	char t;
	
	if (level == 1)	{
		random = rand() % 11;
        
		if (random == 0) {
			t = 'S';
		}
		else if (random == 1) {
			t = 'Z';
		}
		else if (random == 2 || random == 3 ){
			t = 'T';
		}
		else if (random == 4 || random == 5 ){
			t = 'I';
		}
		else if (random == 6 || random == 7 ){
			t = 'J';
		}
		else if (random == 8 || random == 9 ){
			t = 'L';
		}
		else if (random == 10 || random == 11 ){
			t = 'O';
		}
	}
    
	else if (level == 2) {
		random = rand() % 6;
		if (random == 0) {
			t = 'S';
		}
		else if (random == 1) {
			t = 'Z';
		}
		else if (random == 2){
			t = 'T';
		}
		else if (random == 3){
			t = 'I';
		}
		else if (random == 4){
			t = 'J';
		}
		else if (random == 5){
			t = 'L';
		}
		else if (random == 6){
			t = 'O';
		}
	}
    
	else if (level == 3)	{
		random = rand() % 8;
        
		if (random == 0 || random == 1)	{
			t = 'S';
		}
		else if (random == 2 || random == 3){
			t = 'Z';
		}
		else if (random == 4){
			t = 'J';
		}
		else if (random == 5){
			t = 'L';
		}
		else if (random == 6){
			t = 'O';
		}
		else if (random == 7){
			t = 'I';
		}
		else if (random == 8){
			t = 'T';
		}
	}
	return t;
}


void Game::restart() {
	hiscore = board->hiscore;
	delete board;
	start();
}

void Game::start() {
	board = new Board(18, 10, textOnly);
    board->level = startlevel;
	board->hiscore = hiscore;
	string typeseq = readfile();
    int i = 0;
	int skipped = 0;
	if(board->level == 0) {
	    board->genBlock(typeseq[0], typeseq[1]);
    } else {
    	board->genBlock(genlevelblock(board->level),genlevelblock(board->level));
    }
	cout << *board;
	if (!textOnly) {
        board->xw->fillRectangle(1, 92, 1, 469, 1);
        for(int i = 0; i < 10; i++) {
            board->xw->fillRectangle(i + 25 * i, 92, 1, 468, 1);
        }
        for(int j = 0; j < 18; j++) {
            board->xw->fillRectangle(0, 92 + 25 * j + j, 261, 1, 1);
        }
		board->drawBoard();
	}
	i += 2;
	string command;
	while (cin >> command) {
		int num = 0;
		for (int i = 0; ((command[i] >= '0') && (command[i] <= '9')); i++) {
			num++;
		}
		int steps = 1;
		if (num > 0) {
			istringstream ss(command.substr(0, num));
			ss >> steps;
		}
		
		if (command.substr(num, 3) == "lef") {
			for (int i = 0; i < steps; i++) {
				board->left();
			}
		}
		if (command.substr(num, 2) == "ri") {
			for (int i = 0; i < steps; i++) {
				board->right();
			}
		}
		if (command.substr(num, 2) == "do") {
			for (int i = 0; i < steps; i++) {
				board->down();
			}
		}
		if (command.substr(num, 2) == "cl") {
			for (int i = 0; i < steps; i++) {
				board->rotate(1, "clockwise");
			}
		}
		if (command.substr(num, 2) == "co") {
			for (int i = 0; i < steps; i++) {
				board->rotate(1, "counterclockwise");
			}
		}
		if (command.substr(num, 2) == "dr") {
			char type;
			if(board->level == 0)  {
                type = typeseq[i];
		    } else {
                type = genlevelblock(board->level);
		    }
			board->drop(type);
			i++;
			skipped = 0;
		}
		if (command.substr(num, 6) == "levelu") {
			for (int i = 0; i < steps; i++) {
				if(board->level < 3) {
					board->level++;
		   		}
			}
			skipped = 0;
		}
		if (command.substr(num, 6) == "leveld") {
			for (int i = 0; i < steps; i++) {
				if(board->level >0) {
            		board->level--;
		    	}
			}
			skipped = 0;
		}
		if (command.substr(num, 2) == "re") {
			restart();
			skipped = 0;
		}
		if (command.substr(num, 1) == "s") {
			char type;
			i++;
			if (skipped < 2) {
				if (board->level == 0) {
					type = typeseq[i];
				} else {
					type = genlevelblock(board->level);
				}
				board->skip(type);
				skipped++;
			}
		}
		cout << *board;
		
		if (!textOnly) {
			board->xw->fillRectangle(0,0,500,90,0);
			board->xw->fillRectangle(50,565,450,60,0);
			board->drawBoard();
		}
		
		if(board->gameend) {
			board->xw->fillRectangle(0,0,500,650,0);
			board->gameover();
		}
	}
	
}




void Game::end() {
    delete board;
	delete this;
}

void Game::srtLevel(int n) {
	startlevel = n;
}
void Game::textonly() {
	textOnly = true;
}

void Game::setfile(std::string filename) {
	scriptfile = filename;
}

