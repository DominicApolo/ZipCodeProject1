#ifndef EXTREMATABLE_H
#define EXTREMATABLE_H

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
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

class ExtremaTable {
   private:
    std::map<std::string, Extrema> table;

   public:
    ExtremaTable();
    void update(const Place place);

    // void print() {
    //     for (map<std::string, Extrema >::const_iterator it = table.begin();
    //          it != table.end(); ++it) {
    //         std::cout << it->first << " " << "\n";
    //     }
    // }
};

#endif