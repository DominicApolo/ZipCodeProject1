/* This file contains the record details like zipcode, State ID, longitude and latitude.
We have the unpack and read functions that
puts the data from CSV file into the buffer and reads the data from CSV file. */
#ifndef PLACE_H
#define PLACE_H

#include <string>

#include "CsvBuffer.h"

class Place {
   public:
    Place();

    /**
     * @brief Copy constructor
     *
     * @param loc
     */
    Place(const Place& loc);

    /**
     * @brief Returns the Zip Code
     *
     * @return std::string
     */
    std::string getZipCode() const;

    /**
     * @brief Returns the 2 digit State Id
     *
     * @return std::string
     */
    std::string getState() const;

    /**
     * @brief Returns the Place Name
     *
     * @return std::string
     */
    std::string getName() const;

    /**
     * @brief Returns the County
     *
     * @return std::string
     */
    std::string getCounty() const;

    /**
     * @brief Returns the latitude
     *
     * @return double
     */
    double getLat() const;

    /**
     * @brief Returns the longitude
     *
     * @return double
     */
    double getLongi() const;

    /**
     * @brief Reads a record from the buffer and unpacks the fields into the class members
     *
     * @param[in, out] buffer The buffer to be read from
     *
     * @pre buffer has a record that contains zipcode, place name, state id, county, latitude, and longitude fields
     *
     * @post the member variables have been set to the values mentioned above, if the column with that name was found
     */
    void unpack(CsvBuffer& buffer);

    /**
     * @brief Assignment operator overload
     * 
     * @param loc The place object that this one's parameters will match
     */
    void operator=(const Place& loc);

   private:
    std::string zipcode;
    std::string name;
    std::string state;
    std::string county;
    double latitude;
    double longitude;
};
#endif