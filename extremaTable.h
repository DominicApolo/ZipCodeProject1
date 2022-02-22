#ifndef EXTREMATABLE_H
#define EXTREMATABLE_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Place.h"

struct Extreme {
    std::string zip; 
    double coord; /// the latitude or longitude of the place
};

struct Extrema {
    /// The northern most extreme
    Extreme north; 
    /// The southern most extreme
    Extreme south;
    /// The eastern most extreme 
    Extreme east; 
    /// The western most extreme
    Extreme west; 
};

/**
 * @brief Outputs a line of formatting characters
 * 
 * @param os the stream that the line will be sent to 
 * @param first the first character to be sent
 * @param between the middle character(s) that will be sent
 * @param end the last character to be sent
 * @param width the number of middle characters to send
 * @return std::ostream& return the stream for reuse
 */
std::ostream& ExtraText(std::ostream& os, char first, char between, char end, const size_t width);

// maps a state id string to an extrema struct that contains the zip codes of the north, south, east, and westernmost zip codes
class ExtremaTable {
   private:
    // note that the keys of std::map are sorted in ascending order by default
    std::map<std::string, Extrema> table;

   public:
    ExtremaTable();

    /**
     * @brief Checks if the place passed in is an extreme of the state. If it is, then the corresponding record in the table is updated. If it is not, nothing happens. 
     * 
     * @param[in] place the place to be checked for extrema
     * 
     * @post If the place passed in is an extreme of the state, then the corresponding record in the table is updated. If it is not, nothing happens.
     */
    void update(const Place place);

    /**
     * @brief Sends a formatted table containing the state id and the eastern, western, northern, and southernmost, in that order, zip codes in the state
     * 
     * @param os the stream to send the table to
     * @param extremaTable the table to be output
     * 
     * @pre os is an open ostream
     * @post a formatted table has been output to the stream
     * 
     * @return std::ostream& return the stream for reuse
     */
    friend std::ostream& operator<<(std::ostream& os, const ExtremaTable& extremaTable);
    
    /**
     * @brief returns the headers vector
     * 
     * @return std::vector<std::string> 
     */
    std::vector<std::string> getHeaders();
};

#endif