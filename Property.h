//
// Created by Andrew Eeckman on 2/1/18.
//

#ifndef HOARDINGCPP_PROPERTY_H
#define HOARDINGCPP_PROPERTY_H

//**********************************************************************************************************************************

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>

//**********************************************************************************************************************************

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

//**********************************************************************************************************************************

namespace Monopoly {

    class propertyType {
    public:
        propertyType();

        void setType(const string &typeIn) {
            type.assign(typeIn);
        }
        void setSetID(int set) {
            setID = set;
        }
        void setIntraID(int intra) {
            intraID = intra;
        }
        void setName(const string &nameIn) {
            name.assign(nameIn);
        }
        void setPropertyCost(int cost) {
            propertyCost = cost;
        }
        void setHouseCost(int hCost) {
            houseCost = hCost;
        }
        void setHotelCost(int htCost) {
            hotelCost = htCost;
        }
        void setRent(int r) {
            rent = r;
        }
        void setRentHouse(int hRent) {
            rentWithHouse = hRent;
        }
        void setRentHotel(int htRent) {
            rentWithHotel = htRent;
        }
        void setOwned(bool o) {
            owned = o;
        }
        void setOwnedBy(int by) {
            ownedBy = by;
        }
        void setPositionOnBoard(int pos) {
            positionOnBoard = pos;
        }

        string getType() {
            return type;
        }
        int getSetID() {
            return setID;
        }
        int getIntraID() {
            return intraID;
        }
        string getName() {
            return name;
        }
        int getPropertyCost() {
            return propertyCost;
        }
        int getHouseCost() {
            return houseCost;
        }
        int getHotelCost() {
            return hotelCost;
        }
        int getRent() {
            return rent;
        }
        int getRentHouse() {
            return rentWithHouse;
        }
        int getRentHotel() {
            return rentWithHotel;
        }
        bool getOwned() {
            return owned;
        }
        int getOwnedBy() {
            return ownedBy;
        }
        int getPositionOnBoard() {
            return positionOnBoard;
        }
        //propertyType readInProperty(ifstream);

    private:
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

        bool owned;
        int ownedBy;

        int positionOnBoard;
    };

    class goType {
    public:
        goType();

        void setType(string t) {
            type.assign(t);
        }
        void setMoneyAroundGo(int money) {
            moneyAroundGo = money;
        }
        void setName(string n) {
            name.assign(n);
        }

        string getType() {
            return type;
        }
        int getMoneyAroundGo() {
            return moneyAroundGo;
        }
        string getName() {
            return name;
        }

    private:
        string type;
        int moneyAroundGo;
        string name;
    };

    class boardSpace {
    public:
        boardSpace();
        goType goSpace;
        propertyType propertySpace;
    };
}

//**********************************************************************************************************************************

#endif //HOARDINGCPP_PROPERTY_H
