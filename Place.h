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
    void setZipCode(std::string val);

    std::string getState() const;
    void setState(std::string val);

    std::string getName() const;
    void setName(std::string val);

    std::string getCounty() const;
    void setCounty(std::string val);

    float getLat() const;
    void setLat(float val);

    float getLongi() const;
    void setLongi(float val);

    void unpack(CsvBuffer& buffer);

    void operator=(const Place& loc);
    bool operator<(const Place& loc) const;
    bool operator>(const Place& loc) const;
    void print();

   private:
    std::string zipcode;
    std::string name;
    std::string state;
    std::string county;
    float latitude;
    float longitude;
};
// Default constructor

#endif