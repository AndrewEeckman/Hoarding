//
// Created by Andrew Eeckman on 2/7/18.
//

#include "Property.h"


#ifndef HOARDINGCPP_SPACE_H
#define HOARDINGCPP_SPACE_H

namespace Monopoly {
    class boardSpace {
    public:
        boardSpace();
        goType goSpace;
        propertyType propertySpace;
    };
}


#endif //HOARDINGCPP_SPACE_H
