//
// Created by Andrew Eeckman on 2/1/18.
//

#ifndef HOARDINGCPP_PROPERTY_H
#define HOARDINGCPP_PROPERTY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;



namespace Monopoly {
    class propertyType {
    public:
        propertyType();
        //propertyType readInProperty(ifstream);
        string type;
        int setID;
        int intraID;
        string name;
        int propertyCost;
        int houseCost;
        int hotelCost;
        int rent;
        int rentWithHouse;
        int rentWithHotel;
    };

    class goType {
    public:
        goType();
        //goType readInGo(ifstream);
        string type;
        int moneyAroundGo;
        string name;
    };
}

#endif //HOARDINGCPP_PROPERTY_H
