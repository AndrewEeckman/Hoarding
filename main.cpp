#include <iostream>
#include <fstream>
#include <string>
#include "Rules.h"
#include "Board.h"

using namespace Monopoly;
using std::cout;
using std::cin;
using std::endl;

int main(int argc, char* argv[]) {
    Rules rules;
    Board board;

    //readInRules(game, argv[1]);

    rules.readInRules(argv[1]);

    cout << rules.getStartingCash() << endl;

    board.readInBoard(argv[2]);

    return 0;
}

