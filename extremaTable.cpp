#include "extremaTable.h"

ExtremaTable::ExtremaTable() {}

/**
 * @brief
 *
 * @param os
 * @param extreme
 * @return std::ostream&
 */
std::ostream& operator<<(std::ostream& os, const Extreme& extreme) {
    return os << "zip code: " << extreme.zip << std::endl
              << "coord: " << extreme.coord << std::endl;
}

/**
 * @brief
 *
 * @param os
 * @param extrema
 * @return std::ostream&
 */
std::ostream& operator<<(std::ostream& os, const Extrema& extrema) {
    return os << "north: " << extrema.north << std::endl;
    return os << "south: " << extrema.south << std::endl;
    return os << "east: " << extrema.east << std::endl;
    return os << "west: " << extrema.west << std::endl;
}

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

        if (place.getLat() > extrema.north.coord) {
            extrema.north = {place.getZipCode(), place.getLat()};
        }
        if (place.getLat() < extrema.south.coord) {
            extrema.south = {place.getZipCode(), place.getLat()};
        }
        if (place.getLongi() < extrema.east.coord) {
            extrema.east = {place.getZipCode(), place.getLongi()};
        }
        if (place.getLongi() > extrema.west.coord) {
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