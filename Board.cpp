//
// Created by Andrew Eeckman on 1/31/18.
//

#include "Board.h"

Monopoly::Board::Board() {
    goSpace.name.assign(" ");
    goSpace.moneyAroundGo = 0;
}

void Monopoly::Board::readInBoard(char *argv) {
    ifstream readIn(argv);
    string tempGo;

    char delim = ',';
    size_t pos = 0;
    int i = 0;

    if(!readIn.is_open()) {
        cout << "Error opening file" << endl;
    }

    readIn.ignore(256, ',');
    readIn >> numOfSpaces;
    while(i < 4) {
        readIn.ignore(256, '\n');
        i++;
    }

    getline(readIn, goSpace.type, delim);
    readIn >> goSpace.moneyAroundGo;
    readIn.ignore(256, ',');
    getline(readIn, goSpace.name, delim);
    readIn.ignore(256, '\n');

    //Type,Set Id,Intraset Id,Name,Property Cost,House Cost,Hotel Cost,Rent,Rent with House,Rent With Hotel

    propertySpace = new propertyType[numOfSpaces-1];

    for(i = 0; i < (numOfSpaces - 1); i++) {
        getline(readIn, propertySpace[i].type, delim);
        readIn >> propertySpace[i].setID;
        readIn.ignore(256, ',');
        readIn >> propertySpace[i].intraID;
        readIn.ignore(256, ',');
        getline(readIn, propertySpace[i].name, delim);
        readIn >> propertySpace[i].propertyCost;
        readIn.ignore(256, ',');
        readIn >> propertySpace[i].houseCost;
        readIn.ignore(256, ',');
        readIn >> propertySpace[i].hotelCost;
        readIn.ignore(256, ',');
        readIn >> propertySpace[i].rent;
        readIn.ignore(256, ',');
        readIn >> propertySpace[i].rentWithHouse;
        readIn.ignore(256, ',');
        readIn >> propertySpace[i].rentWithHotel;
        readIn.ignore(256, '\n');
    }

    cout << numOfSpaces << endl;
    cout << goSpace.type << " " << goSpace.moneyAroundGo << " " << goSpace.name << endl;

    for(i = 0; i < (numOfSpaces - 1); i++) {
        cout << propertySpace[i].type << " " << propertySpace[i].setID
             << " " << propertySpace[i].intraID << " " << propertySpace[i].name << " "
             << propertySpace[i].propertyCost << " " << propertySpace[i].houseCost << " " << propertySpace[i].hotelCost
             << " " << propertySpace[i].rent << " " << propertySpace[i].rentWithHouse << " " << propertySpace[i].rentWithHotel << endl;
    }
}
