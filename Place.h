/* This file contains the record details like zipcode, State ID, longitude and latitude.
We have the unpack and read functions that
puts the data from CSV file into the buffer and reads the data from CSV file. */
#ifndef PLACE_H
#define PLACE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "CsvBuffer.h"

class Place {
   public:
    Place();
    Place(const Place& loc);

    std::string getZipCode() const;
    std::string getState() const;
    std::string getName() const;
    std::string getCounty() const;
    double getLat() const;
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