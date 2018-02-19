//
// Created by Andrew Eeckman on 2/7/18.
//

#include "DiceRoller.h"

using namespace Monopoly;

DiceRoller::DiceRoller() {
    diceRoll = 0;
}

int DiceRoller::rollDice(ifstream &randomStream) {
    int diceRoll = 0;
    int roll1 = 0;
    int roll2 = 0;

    randomStream >> roll1;
    randomStream >> roll2;

    diceRoll = ((roll1 % 6) + 1) + ((roll2 % 6) + 1);

    return diceRoll;
}
