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
#include <random>

//**********************************************************************************************************************************

namespace Monopoly {
    class GameState {
    public:
        void getMove(Board *board, int currentPlayer);
        void movePlayer(Board *board, int currentPlayer);
    };
}

//**********************************************************************************************************************************

#endif //HOARDINGCPP_GAMESTATE_H
