//
// Created by Andrew Eeckman on 2/7/18.
//

#ifndef HOARDINGCPP_DICEROLLER_H
#define HOARDINGCPP_DICEROLLER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

namespace Monopoly {
    class DiceRoller {
    public:
        DiceRoller();
        int rollDice(ifstream& randomStream);

    private:
        int diceRoll;
    };

}

#endif //HOARDINGCPP_DICEROLLER_H
