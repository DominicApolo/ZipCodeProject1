#include "Place.h"

using std::string;

Place::Place() {
    zipcode = "";
    state = "";
    name = "";
    latitude = 0;
    county = "";
    longitude = 0;
};

// copy constructor
Place::Place(const Place& loc) {
    zipcode = loc.getZipCode();
    name = loc.getName();
    state = loc.getState();
    county = loc.getCounty();
    latitude = loc.getLat();
    longitude = loc.getLongi();
};

string Place::getZipCode() const { return zipcode; }  // zipcode value
// get name
string Place::getName() const { return name; }  // name value
// get state
string Place::getState() const { return state; }  // State value
// get lat
string Place::getCounty() const { return county; }  // county value

float Place::getLat() const { return latitude; }  // Latitude value
// get longitude
float Place::getLongi() const { return longitude; }  // longitude value
// Set zip code
void Place::setZipCode(string val) { zipcode = val; }

// set name
void Place::setName(string val) { name = val; }

// set state
void Place::setState(string val) { state = val; }

// set county
void Place::setCounty(string val) { county = val; }

// Set latitude
void Place::setLat(float val) { latitude = val; }

// Set longtitude
void Place::setLongi(float val) { longitude = val; }

// passing to place object by unpacking from buffer
void Place::unpack(CsvBuffer& buffer) {
    std::string skip;
    string lat_str, long_str;

    bool moreFields = true;
    while (moreFields) {
        auto curField = buffer.getCurFieldHeader();
        switch (curField.first) {
            case HeaderField::ZipCode:
                moreFields = buffer.unpack(zipcode);
                break;
            case HeaderField::PlaceName:
                moreFields = buffer.unpack(name);
                break;
            case HeaderField::State:
                moreFields = buffer.unpack(state);
                break;
            case HeaderField::County:
                moreFields = buffer.unpack(county);
                break;
            case HeaderField::Latitude:
                moreFields = buffer.unpack(lat_str);
                break;
            case HeaderField::Longitude:
                moreFields = buffer.unpack(long_str);
                break;
            default:
                moreFields = buffer.unpack(skip);
                break;

        }
    }

    std::stringstream(lat_str) >> latitude;    // convert to float
    std::stringstream(long_str) >> longitude;  // convert to float
}

// overload the assignment operator
void Place ::operator=(const Place& loc) {
    setZipCode(loc.getZipCode());
    setName(loc.getName());
    setState(loc.getState());
    setCounty(loc.getCounty());
    setLat(loc.getLat());
    setLongi(loc.getLongi());
}

// operator overloaded
bool Place ::operator<(const Place& loc) const {
    return getState() < loc.getState();
}

// operator overloaded
bool Place ::operator>(const Place& loc) const {
    return getState() > loc.getState();
}

void Place::print() {
    std::cout << zipcode << ' '
              << name << ' '
              << state << ' '
              << county << ' '
              << latitude << ' '
              << longitude;
}
