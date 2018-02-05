#include <iostream>
#include <fstream>
#include <string>
#include "Rules.h"
#include "Board.h"
#include "Player.h"
#include "GameState.h"

//**********************************************************************************************************************************

using namespace Monopoly;
using std::cout;
using std::cin;
using std::endl;

//**********************************************************************************************************************************

int main(int argc, char* argv[]) {
    Rules rules;
    Board board;
    GameState game;
    int currentPlayer = 0;
    int i = 0;

    //readInRules(game, argv[1]);

    board.readInRules(argv[1]);

    board.readInBoard(argv[2], &board);

    board.initiatePlayers(&board);

    board.displayBoard(&board);

    while(true) {
        game.getMove(&board, i % board.getPlayerNumber());
        i++;
    }

    return 0;
}

//**********************************************************************************************************************************

