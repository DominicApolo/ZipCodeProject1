#include "extremaTable.h"

ExtremaTable::ExtremaTable() {}

// gets a place as input
// checks to see if place is in the map already
// if it is, it checks each of the new place's lat and long against the current most extreme and
// replaces it if it is more extreme
// if it is not in the map, it records the zip code of the place as the most extreme in all four directions
/**
 * @brief
 *
 * @param place
 */
void ExtremaTable::update(const Place place) {
    auto it = table.find(place.getState());
    if (it != table.end()) {
        auto& extrema = it->second;

        // was running into an issue with the Micronesian zip codes (state id FM)
        // there are four zip codes all with the same coordinates.
        // The zip code that would get recorded was the one that was came first in the file.
        // So when the file was sorted on a different column it was possible to get a different
        // zip code for the same coordinates. To deal with this, I just check to see if the coordinates
        // are equal, then take the largest zip code with those coordinates.

        // check north
        if (place.getLat() > extrema.north.coord) {
            extrema.north = {place.getZipCode(), place.getLat()};
        } else if (place.getLat() == extrema.north.coord && place.getZipCode() > extrema.north.zip) {
            extrema.north = {place.getZipCode(), place.getLat()};
        }

        // check south
        if (place.getLat() < extrema.south.coord) {
            extrema.south = {place.getZipCode(), place.getLat()};
        } else if (place.getLat() == extrema.south.coord && place.getZipCode() > extrema.south.zip) {
            extrema.south = {place.getZipCode(), place.getLat()};
        }

        // check east
        if (place.getLongi() < extrema.east.coord) {
            extrema.east = {place.getZipCode(), place.getLongi()};
        } else if (place.getLongi() == extrema.east.coord && place.getZipCode() > extrema.east.zip) {
            extrema.east = {place.getZipCode(), place.getLongi()};
        }

        // check west
        if (place.getLongi() > extrema.west.coord) {
            extrema.west = {place.getZipCode(), place.getLongi()};
        } else if (place.getLongi() == extrema.west.coord && place.getZipCode() > extrema.west.zip) {
            extrema.west = {place.getZipCode(), place.getLongi()};
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

/**
 * @brief
 *
 * @param os
 * @param first
 * @param between
 * @param end
 * @param width
 * @return std::ostream&
 */
std::ostream& ExtraText(std::ostream& os, char first, char between, char end, const size_t width) {
    os << first;
    for (unsigned short i = 0; i < 5; i++)
        os << std::string(width, '-') << ((i == 4) ? end : between);

    return os << std::endl;
}

/**
 * @brief
 *
 * @param os
 * @param extrema
 * @return std::ostream&
 */
std::ostream& operator<<(std::ostream& os, const ExtremaTable& extrema) {
    ExtraText(os, '-', '-', '-', 7);
    char l = '|';

    os << l << "State\t"
       << l << "East\t"
       << l << "West\t"
       << l << "North\t"
       << l << "South\t"
       << l << std::endl;

    ExtraText(os, '-', '-', '-', 7);

    for (auto& it : extrema.table) {
        os << l << it.first << "\t"
           << l << it.second.east.zip << "\t"
           << l << it.second.west.zip << "\t"
           << l << it.second.north.zip << "\t"
           << l << it.second.south.zip << "\t"
           << l << std::endl;
    }
    ExtraText(os, '-', '-', '-', 7);

    return os;
}