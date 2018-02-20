//
// Created by Andrew Eeckman on 2/1/18.
//

#include "Property.h"

using namespace Monopoly;

//**********************************************************************************************************************************

propertyType::propertyType() {
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

goType::goType() {
    type.assign("Go");
    moneyAroundGo = 0;
    name.assign(" ");
}

//**********************************************************************************************************************************
