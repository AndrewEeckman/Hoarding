//
// Created by Andrew Eeckman on 1/31/18.
//

//**********************************************************************************************************************************

#include "Rules.h"
#include <fstream>

//**********************************************************************************************************************************

Monopoly::Rules::Rules() {
    startingCash = 0;
    turnLimit = 0;
    numOfPlayerToEndGame = 0;
    propertySetMultiplier = 0;
    numHousesBeforeHotels = 0;
    buildHousesEvenly = false;         //NOT USING
    putMoneyInFreeParking = false;     //NOT USING
    auctionProperties = false;         //NOT USING
    salMultiLandingOnGo = 0;
}

//**********************************************************************************************************************************

int Monopoly::Rules::getStartingCash() {
    return startingCash;
}

int Monopoly::Rules::getTurnLimit() {
    return turnLimit;
}

int Monopoly::Rules::getPlayersToEndGame() {
    return numOfPlayerToEndGame;
}

int Monopoly::Rules::getSetMulti() {
    return propertySetMultiplier;
}

int Monopoly::Rules::getHousesBefore() {
    return numHousesBeforeHotels;
}

bool Monopoly::Rules::getBuildEvenly() {
    return buildHousesEvenly;
}

bool Monopoly::Rules::getFreeParking() {
    return putMoneyInFreeParking;
}

bool Monopoly::Rules::getAuction() {
    return auctionProperties;
}

int Monopoly::Rules::getSalMultiGo() {
    return salMultiLandingOnGo;
}

//**********************************************************************************************************************************

void Monopoly::Rules::readInRules(char *argv) {
    ifstream rulesIn(argv);

    string tempBuildEvenly;
    string tempFreeParking;
    string tempAuction;

    if(!rulesIn.is_open()) {
        cout << "Error opening file" << endl;
    }

    rulesIn.ignore(256, ':');
    rulesIn >> startingCash;
    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');
    rulesIn >> turnLimit;
    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');
    rulesIn >> numOfPlayerToEndGame;
    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');
    rulesIn >> propertySetMultiplier;
    rulesIn.ignore(256, '\n');
    rulesIn.ignore(256, ':');
    rulesIn >> numHousesBeforeHotels;
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
    rulesIn >> salMultiLandingOnGo;

    if(tempBuildEvenly == "Yes") {
        buildHousesEvenly = true;
    }

    if(tempFreeParking == "Yes") {
        putMoneyInFreeParking = true;
    }

    if(tempAuction == "Yes") {
        auctionProperties = true;
    }
}

//**********************************************************************************************************************************
