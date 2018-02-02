//
// Created by Andrew Eeckman on 1/31/18.
//

#ifndef HOARDINGCPP_BOARDMANAGER_H
#define HOARDINGCPP_BOARDMANAGER_H

#include "Property.h"
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

    class Board : public propertyType , public goType {
    public:
        Board();
        void readInBoard(char argv[]);
        //void displayBoard(boardSpace *board, int numOfSpaces, int numOfPlayers);

    private:
        goType goSpace;
        propertyType* propertySpace;
        int numOfSpaces;
    };
}


#endif //HOARDINGCPP_BOARDMANAGER_H
