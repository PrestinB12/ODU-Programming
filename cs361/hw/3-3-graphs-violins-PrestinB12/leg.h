#ifndef LEG_H
#define LEG_H

#include <iostream>
#include <string>

struct Leg {
    std::string fromCity;
    std::string toCity;
    std::string road;
    double distance;

    bool operator== (const Leg& leg) const;
};

std::ostream& operator<< (std::ostream& out, const Leg& leg);

#endif