/* This file contains the record details like zipcode, State ID, longitude and latitude. 
We have the unpack and read functions that
puts the data from CSV file into the buffer and reads the data from CSV file. */

#ifndef PLACE_H
#define PLACE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "BuffClass.h"

class Place
{
public:

	Place();
	Place(const Place & loc);

	string getZipCode() const;
	void setZipCode(string val);

	string getState() const;
	void setState(string val);

	string getName() const;
	void setName(string val);

	string getCounty() const;
	void setCounty(string val);

	float getLat() const;
	void setLat(float val);

	float getLongi() const;
	void setLongi(float val);

	bool unpack(BuffClass& buffer);
	

	void operator =(const Place& loc);
	bool operator <(const Place& loc)const;
	bool operator >(const Place& loc)const;

private:
	string zipcode;
	string name;
	string state;
	string county;
	float latitude;
	float longitude;
};
//Default constructor
Place::Place()
{
	zipcode = " ";
	state = " ";
	name = " ";
	latitude = 0;
	county = " ";
	longitude = 0;
};

//copy constructor
Place::Place(const Place& loc)
{
	zipcode = loc.getZipCode();
	name = loc.getName();
	state = loc.getState();
	county = loc.getCounty();
	latitude = loc.getLat();
	longitude = loc.getLongi();
};

//get zip code
string Place::getZipCode() const { return zipcode; } // zipcode value
//get name
string Place::getName() const { return name; }//name value
//get state
string Place::getState() const { return state; } // State value
//get lat
string Place::getCounty() const { return county; }//county value

float Place::getLat() const { return latitude; } // Latitude value
// get longitude
float Place::getLongi() const { return longitude; } // longitude value
// Set zip code
void Place::setZipCode(string val) { zipcode = val; }

//set name
void Place::setName(string val) { name = val; }

//set state
void Place::setState(string val) { state = val; }

//set county
void Place::setCounty(string val) { county = val; }

//Set latitude
void Place::setLat(float val) { latitude = val; }

//Set longtitude
void Place::setLongi(float val) { longitude = val; }

//passing to place object by unpacking from buffer
bool Place::unpack(BuffClass& buffer)
{
	bool result;
	string flush;
	result = buffer.unpack(zipcode);
	result = result && buffer.unpack(flush);
	result = result && buffer.unpack(state);
	result = result && buffer.unpack(flush);
	string lat_str, long_str;
	result = result && buffer.unpack(lat_str);
	result = result && buffer.unpack(long_str);
	stringstream(lat_str) >> latitude; //convert to float
	stringstream(long_str) >> longitude; //convert to float	
	return result;
}

//overload the assignment operator
void Place :: operator= (const Place& loc) 
{
	setZipCode(loc.getZipCode());
	setName(loc.getName());
	setState(loc.getState());
	setCounty(loc.getCounty());
	setLat(loc.getLat());
	setLongi(loc.getLongi());
}

//operator overloaded
bool Place :: operator< (const Place& loc) const
{
	return getState() < loc.getState();
}

//operator overloaded
bool Place :: operator> (const Place& loc) const
{
	return getState() > loc.getState();
}


#endif


