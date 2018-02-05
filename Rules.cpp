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

void Monopoly::Rules::setStartingCash(int cash) {
    startingCash = cash;
}

void Monopoly::Rules::setTurnLimit(int limit) {
    turnLimit = limit;
}

void Monopoly::Rules::setPlayersToEndGame(int endGameNum) {
    numOfPlayerToEndGame = endGameNum;
}

void Monopoly::Rules::setSetMulti(int setMulti) {
    propertySetMultiplier = setMulti;
}

void Monopoly::Rules::setHousesBefore(int houses) {
    numHousesBeforeHotels = houses;
}

void Monopoly::Rules::setBuildEvenly(bool even) {
    buildHousesEvenly = even;
}

void Monopoly::Rules::setFreeParking(bool free) {
    putMoneyInFreeParking = free;
}

void Monopoly::Rules::setAuction(bool auction) {
    auctionProperties = auction;
}

void Monopoly::Rules::setSalMultiGo(int salMulti) {
    salMultiLandingOnGo = salMulti;
}


//**********************************************************************************************************************************
