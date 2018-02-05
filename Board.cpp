//
// Created by Andrew Eeckman on 1/31/18.
//

#include "Board.h"
#include "Property.h"

//**********************************************************************************************************************************

Monopoly::Board::Board() {
    numOfSpaces = 0;
}

//**********************************************************************************************************************************

void Monopoly::Board::readInBoard(char *argv, Board *board) {
    ifstream readIn(argv);

    string tempType;
    string tempName;
    int tempMoneyAroundGo;
    int tempSetID;
    int tempIntraID;
    int tempPropCost;
    int tempHouseCost;
    int tempHotelCost;
    int tempRent;
    int tempRentWHouse;
    int tempRentWHotel;

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
    (*board).boardSpaces.assign(static_cast<unsigned long>(numOfSpaces), boardSpace());

    getline(readIn, tempType, delim);
    (*board).boardSpaces.at(0).goSpace.setType(tempType);
    tempType.clear();

    readIn >> tempMoneyAroundGo;
    (*board).boardSpaces.at(0).goSpace.setMoneyAroundGo(tempMoneyAroundGo);
    tempMoneyAroundGo = 0;

    readIn.ignore(256, ',');

    getline(readIn, tempName, delim);
    (*board).boardSpaces.at(0).goSpace.setName(tempName);
    tempName.clear();

    readIn.ignore(256, '\n');

    //Type,Set Id,Intraset Id,Name,Property Cost,House Cost,Hotel Cost,Rent,Rent with House,Rent With Hotel

    for(i = 1; i < numOfSpaces; i++) {
        getline(readIn, tempType, delim);
        (*board).boardSpaces.at(i).propertySpace.setType(tempType);
        tempType.clear();

        readIn >> tempSetID;
        (*board).boardSpaces.at(i).propertySpace.setSetID(tempSetID);

        readIn.ignore(256, ',');

        readIn >> tempIntraID;
        (*board).boardSpaces.at(i).propertySpace.setIntraID(tempIntraID);

        readIn.ignore(256, ',');

        getline(readIn, tempName, delim);
        (*board).boardSpaces.at(i).propertySpace.setName(tempName);
        tempName.clear();

        readIn >> tempPropCost;
        (*board).boardSpaces.at(i).propertySpace.setPropertyCost(tempPropCost);

        readIn.ignore(256, ',');

        readIn >> tempHouseCost;
        (*board).boardSpaces.at(i).propertySpace.setHouseCost(tempHouseCost);

        readIn.ignore(256, ',');

        readIn >> tempHotelCost;
        (*board).boardSpaces.at(i).propertySpace.setHotelCost(tempHotelCost);

        readIn.ignore(256, ',');

        readIn >> tempRent;
        (*board).boardSpaces.at(i).propertySpace.setRent(tempRent);

        readIn.ignore(256, ',');

        readIn >> tempRentWHouse;
        (*board).boardSpaces.at(i).propertySpace.setRentHouse(tempRentWHouse);

        readIn.ignore(256, ',');

        readIn >> tempRentWHotel;
        (*board).boardSpaces.at(i).propertySpace.setRentHotel(tempRentWHotel);

        readIn.ignore(256, '\n');

        (*board).boardSpaces.at(i).propertySpace.setOwned(false);
        (*board).boardSpaces.at(i).propertySpace.setOwnedBy(-1);
        (*board).boardSpaces.at(i).propertySpace.setPositionOnBoard(i);
    }

    cout << numOfSpaces << endl;
    cout << (*board).boardSpaces.at(0).goSpace.getType() << " " << (*board).boardSpaces.at(0).goSpace.getMoneyAroundGo()
         << " " << (*board).boardSpaces.at(0).goSpace.getName() << endl;

    for(i = 1; i < numOfSpaces; i++) {
        cout << (*board).boardSpaces.at(i).propertySpace.getType() << " " << (*board).boardSpaces.at(i).propertySpace.getSetID()
             << " " << (*board).boardSpaces.at(i).propertySpace.getIntraID() << " " << (*board).boardSpaces.at(i).propertySpace.getName() << " "
             << (*board).boardSpaces.at(i).propertySpace.getPropertyCost() << " " << (*board).boardSpaces.at(i).propertySpace.getHouseCost() << " "
             << (*board).boardSpaces.at(i).propertySpace.getHotelCost() << " " << (*board).boardSpaces.at(i).propertySpace.getRent() << " "
             << (*board).boardSpaces.at(i).propertySpace.getRentHouse() << " " << (*board).boardSpaces.at(i).propertySpace.getRentHotel() << endl;
    }
}

//**********************************************************************************************************************************

void Monopoly::Board::displayBoard(Board *board) {
    int count = 0;

    cout << "Space Number| Space Name\t| Owners\t| Players" << endl;

    for(int i = 0; i < numOfSpaces; i++) {

        if(i == 0) {
            cout << "0\t\t\t| " << (*board).boardSpaces.at(0).goSpace.getName() << "\t\t\t| None\t\t| ";

            for(int j = 0; j < numOfPlayers; j++){
                if(players.at(j).getBoardPosition() == 0) {
                    if (count >= 1) {
                        cout << ", ";
                    }
                    cout << "[" << players.at(j).getName() << " : " << players.at(j).getCashAmount() << "] ";
                    count++;
                }
            }

            count = 0;

        } else {
            cout << (*board).boardSpaces.at(i).propertySpace.getPositionOnBoard() << "\t\t\t| " << (*board).boardSpaces.at(i).propertySpace.getName() << "\t\t\t\t| ";

            if((*board).boardSpaces.at(i).propertySpace.getOwned()) {
                //FIXME: Do something here
            } else {
                cout << "None\t\t| ";
            }

            for(int j = 0; j < numOfPlayers; j++){
                if(players.at(j).getBoardPosition() == (*board).boardSpaces.at(i).propertySpace.getPositionOnBoard()) {
                    if(count > 0) {
                        cout << ", ";
                    }
                    cout << "[" << players.at(j).getName() << " : " << players.at(j).getCashAmount() << "]";
                    count++;
                }
            }

            count = 0;
        }

        cout << endl;
    }
}

//**********************************************************************************************************************************

void Monopoly::Board::initiatePlayers(Board *board) {

    string tempName;

    cout << "Enter how many players will be playing: ";
    cin >> numOfPlayers;

    (*board).players.assign(static_cast<unsigned long>(numOfPlayers), Player());

    for(int i = 0; i < numOfPlayers; i++) {
        (*board).players.at(i).setBoardPosition(0);
        (*board).players.at(i).setNumIdentifier(i+1);
        (*board).players.at(i).setCashAmount(rules.getStartingCash());
        (*board).players.at(i).setInGame(true);
        (*board).players.at(i).setNetWorth(rules.getStartingCash());

        cout << "Enter the name of player " << (i + 1) << ": ";
        cin >> tempName;
        (*board).players.at(i).setName(tempName);
        tempName.clear();
    }
}

//**********************************************************************************************************************************

void Monopoly::Board::readInRules(char *argv) {
    ifstream rulesIn(argv);

    int tempStartingCash;
    int tempTurnLimit;
    int tempNumOfPlayerToEndGame;
    int tempPropertySetMultiplier;
    int tempNumHousesBeforeHotels;
    int tempSalMultiLandingOnGo;

    string tempBuildEvenly;
    string tempFreeParking;
    string tempAuction;

    if(!rulesIn.is_open()) {
        cout << "Error opening file" << endl;
    }

    rulesIn.ignore(256, ':');

    rulesIn >> tempStartingCash;
    rules.setStartingCash(tempStartingCash);

    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');

    rulesIn >> tempTurnLimit;
    rules.setTurnLimit(tempTurnLimit);

    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');

    rulesIn >> tempNumOfPlayerToEndGame;
    rules.setPlayersToEndGame(tempNumOfPlayerToEndGame);

    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');

    rulesIn >> tempPropertySetMultiplier;
    rules.setSetMulti(tempPropertySetMultiplier);

    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');

    rulesIn >> tempNumHousesBeforeHotels;
    rules.setHousesBefore(tempNumHousesBeforeHotels);

    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');

    rulesIn >> tempBuildEvenly;

    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');

    rulesIn >> tempFreeParking;

    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');

    rulesIn >> tempAuction;

    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');

    rulesIn >> tempSalMultiLandingOnGo;
    rules.setSalMultiGo(tempSalMultiLandingOnGo);

    if(tempBuildEvenly == "Yes") {
        rules.setBuildEvenly(true);
    }

    if(tempFreeParking == "Yes") {
        rules.setFreeParking(true);
    }

    if(tempAuction == "Yes") {
        rules.setAuction(true);
    }
}

//**********************************************************************************************************************************
