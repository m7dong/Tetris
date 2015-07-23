#include "cell.h"
#include "block.h"
#include "board.h"
#include "game.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
	
	Game* game = new Game();
	
	for (int i = 0; i < argc; i++) {
        
		string s = argv[i];
		
		if (s == "-text") {
			game->textonly();
		}
		if (s == "-seed") {
		    int num;
		    stringstream ss(argv[i + 1]);
		    ss >> num;
		    srand(num);
	    }
		if (s == "-scriptfile") {
			game->setfile(argv[i+1]);
			i = i + 1;
		}
		if (s == "-startlevel") {
			int n;
			stringstream ss(argv[i+1]);
			ss >> n;
			game->srtLevel(n);
			i = i + 1;
		}
		
	}
	
	game->start();
	game->end();
	
}

