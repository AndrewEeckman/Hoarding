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
    int playerNumber = 0;

    int i = 0;

    //readInRules(game, argv[1]);

    board.readInRules(argv[1]);

    board.readInBoard(argv[2], &board);

    int playersInGame = board.getPlayerNumber();
    playerNumber = board.getPlayerNumber();

    board.initiatePlayers(&board);


    while(!game.gameOver(&board, i / board.getPlayerNumber(), board.getNumOfPlayersLeft())) {
        game.getMove(&board, i % board.getPlayerNumber());
        i++;
    }

    game.declareWinner(&board, board.getNumOfPlayersLeft());

    return 0;
}

//**********************************************************************************************************************************

