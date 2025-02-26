#include <iostream>
#include <string>

#include "leg.h"

using namespace std;


std::ostream& operator<< (std::ostream& out, const Leg& leg)
{
    out << "From " << leg.fromCity << " take " << leg.road 
        << " to " << leg.toCity << '.';
    return out;
}

bool Leg::operator== (const Leg& leg) const
{
    return fromCity == leg.fromCity
        && toCity == leg.toCity
        && road == leg.road
        && distance == leg.distance;
}
