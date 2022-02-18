#ifndef EXTREMATABLE_H
#define EXTREMATABLE_H

#include <iostream>
#include <map>
#include <string>

#include "Place.h"

struct Extreme {
    std::string zip;
    double coord;
};

struct Extrema {
    Extreme north;
    Extreme south;
    Extreme east;
    Extreme west;
};

std::ostream& operator<<(std::ostream& os, const Extreme& extreme);
std::ostream& operator<<(std::ostream& os, const Extrema& extrema);

// maps a state id string to an extrema struct that contains the zip codes of the north, south, east, and westernmost zip codes
class ExtremaTable {
   public:
    std::map<std::string, Extrema> table;

   public:
    ExtremaTable();
    void update(const Place place);
};

#endif