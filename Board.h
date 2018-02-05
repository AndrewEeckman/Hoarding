//
// Created by Andrew Eeckman on 1/31/18.
//

#ifndef HOARDINGCPP_BOARDMANAGER_H
#define HOARDINGCPP_BOARDMANAGER_H

//**********************************************************************************************************************************

#include "Property.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

//**********************************************************************************************************************************

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

//**********************************************************************************************************************************

namespace Monopoly {

    class Board : public propertyType , public goType {
    public:

        Board();
        void readInBoard(char argv[], Board *board);
        void displayBoard(Board *board);
        void initiatePlayers(Board *board);
        void readInRules(char *argv);

        int getSpaces() {
            return numOfSpaces;
        }

        int getPlayerNumber() {
            return numOfPlayers;
        }

        std::vector<boardSpace>boardSpaces;
        std::vector<Player>players;
        Rules rules;

    private:

        int numOfSpaces;
        int numOfPlayers;
    };
}

//**********************************************************************************************************************************

#endif //HOARDINGCPP_BOARDMANAGER_H
