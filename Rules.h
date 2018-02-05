//
// Created by Andrew Eeckman on 1/31/18.
//

#ifndef HOARDINGCPP_RULEMANAGER_H
#define HOARDINGCPP_RULEMANAGER_H

//**********************************************************************************************************************************

#include <string>
#include <iostream>

//**********************************************************************************************************************************

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

//**********************************************************************************************************************************

namespace Monopoly {
class Rules {
public:
    Rules();

    int getStartingCash();
    int getTurnLimit();
    int getPlayersToEndGame();
    int getSetMulti();
    int getHousesBefore();
    bool getBuildEvenly();
    bool getFreeParking();
    bool getAuction();
    int getSalMultiGo();

    void setStartingCash(int cash);
    void setTurnLimit(int limit);
    void setPlayersToEndGame(int endGameNum);
    void setSetMulti(int setMulti);
    void setHousesBefore(int houses);
    void setBuildEvenly(bool even);
    void setFreeParking(bool free);
    void setAuction(bool auction);
    void setSalMultiGo(int salMulti);


private:
    int startingCash;
    int turnLimit;
    int numOfPlayerToEndGame;
    int propertySetMultiplier;
    int numHousesBeforeHotels;
    bool buildHousesEvenly;         //NOT USING
    bool putMoneyInFreeParking;     //NOT USING
    bool auctionProperties;         //NOT USING
    int salMultiLandingOnGo;
};

}

//**********************************************************************************************************************************

#endif //HOARDINGCPP_RULEMANAGER_H
