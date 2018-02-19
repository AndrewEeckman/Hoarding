//
// Created by Andrew Eeckman on 1/31/18.
//

#ifndef HOARDINGCPP_PLAYERMANAGER_H
#define HOARDINGCPP_PLAYERMANAGER_H

//**********************************************************************************************************************************

#include <string>
#include <iostream>

#include "Rules.h"

//**********************************************************************************************************************************

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

//**********************************************************************************************************************************

namespace Monopoly {

    class Player {
    public:

        Player();

        void setName(const string &n) {
            name.assign(n);
        }
        void setNumIdentifier(int num) {
            numIdentifier = num;
        }
        void setCashAmount(int cash) {
            cashAmount = cash;
        }
        void setNetWorth(int worth) {
            netWorth = worth;
        }
        void setBoardPosition(int pos) {
            boardPosition = pos;
        }
        void setInGame(bool inG) {
            inGame = inG;
        }

        string getName() {
            return name;
        }
        int getNumIdentifier() {
            return numIdentifier;
        }
        int getCashAmount() {
            return cashAmount;
        }
        int getNetWorth() {
            return netWorth;
        }
        int getBoardPosition() {
            return boardPosition;
        }
        bool getInGame() {
            return inGame;
        }

    private:
        string name;
        int numIdentifier;
        int cashAmount;
        int netWorth;
        int boardPosition;
        bool inGame;
    };
}

//**********************************************************************************************************************************

#endif //HOARDINGCPP_PLAYERMANAGER_H
