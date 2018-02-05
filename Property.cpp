//
// Created by Andrew Eeckman on 2/1/18.
//

#include "Property.h"

//**********************************************************************************************************************************

Monopoly::propertyType::propertyType() {
    type.assign("Property");
    name.assign(" ");
    propertyCost = 0;
    houseCost = 0;
    hotelCost = 0;
    rent = 0;
    rentWithHouse = 0;
    rentWithHotel = 0;
}

//**********************************************************************************************************************************

/*
string Monopoly::propertyType::setType(string typeIn) {

}
int Monopoly::propertyType::setSetID(int set) {

}
int Monopoly::propertyType::setIntraID(int intra) {

}
int Monopoly::propertyType::setName(string nameIn) {

}
int Monopoly::propertyType::setPropertyCost(int cost) {

}
int Monopoly::propertyType::setHouseCost(int hCost) {

}
int Monopoly::propertyType::setHotelCost(int htCost);
int Monopoly::propertyType::setRentHouse(int hRent);
int Monopoly::propertyType::setRentHotel(int htRent);

string Monopoly::propertyType::getType();
int Monopoly::propertyType::getSetID();
int Monopoly::propertyType::getIntraID();
int Monopoly::propertyType::getName();
int Monopoly::propertyType::getPropertyCost();
int Monopoly::propertyType::getHouseCost();
int Monopoly::propertyType::getHotelCost();
int Monopoly::propertyType::getRentHouse();
int Monopoly::propertyType::getRentHotel();
*/

//**********************************************************************************************************************************

Monopoly::goType::goType() {
    type.assign("Go");
    moneyAroundGo = 0;
    name.assign(" ");
}

//**********************************************************************************************************************************

Monopoly::boardSpace::boardSpace() = default;

//**********************************************************************************************************************************