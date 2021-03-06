//
// Created by Andrew Eeckman on 2/4/18.
//

#ifndef HOARDINGCPP_GAMESTATE_H
#define HOARDINGCPP_GAMESTATE_H

//**********************************************************************************************************************************

#include "Board.h"
#include "Rules.h"
#include "Player.h"
#include "Property.h"
#include "Space.h"
#include "DiceRoller.h"

//**********************************************************************************************************************************

namespace Monopoly {
    class GameState {
    public:
        void getMove(Board& board, int currentPlayer, ifstream& randomStream);
        bool movePlayer(Board& board, int currentPlayer, ifstream& randomStream);
        void leaveGame(Board& board, int currentPlayer);
        bool gameOver(Board & board, int currentTurnNumber, int playersLeft);
        void declareWinner(Board& board, int playersLeft);

        void purchaseProperty(Board &board, int currentPlayer, int currentBoardPosition, int amountToPay);
        void auctionProperty(Board &board, int currentPlayer, int currentBoardPosition);
    };
}

//**********************************************************************************************************************************

#endif //HOARDINGCPP_GAMESTATE_H
