#include "extremaTable.h"

ExtremaTable::ExtremaTable() {
    
}

void ExtremaTable::update(const Place place) {
    auto it = table.find(place.getState());
    if (it != table.end()) {
        // state in table
        auto extrema = it->second;
        if (place.getLat() > extrema.north.coord) {
            extrema.north = {place.getZipCode(), place.getLat()};
        }
        if (place.getLat() < extrema.south.coord) {
            extrema.south = {place.getZipCode(), place.getLat()};
        }
        if (place.getLongi() < extrema.east.coord) {
            extrema.east = {place.getZipCode(), place.getLat()};
        }
        if (place.getLongi() > extrema.west.coord) {
            extrema.west = {place.getZipCode(), place.getLat()};
        }
    } else {
        // state not in table, record zip as
        Extrema extrema = {
            {place.getZipCode(), place.getLat()},
            {place.getZipCode(), place.getLat()},
            {place.getZipCode(), place.getLongi()},
            {place.getZipCode(), place.getLongi()}};

        table.insert({place.getState(), extrema});
    }
}