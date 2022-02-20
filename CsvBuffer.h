#ifndef CSVBUFFER_H
#define CSVBUFFER_H

#include <istream>
#include <string>
#include <vector>

// idea adapted from https://stackoverflow.com/a/30338543
enum class CSVState {
    QuotedField,
    UnquotedField,
    QuotedQuote
};

enum class HeaderField {
    ZipCode,
    PlaceName,
    State,
    County,
    Latitude,
    Longitude,
    Unknown
};

HeaderField getFieldType (std::string headerValue);

class CsvBuffer {
   public:
    const size_t maxSize;
    const char delim;

    size_t curr;
    std::string buffer;
    size_t head;
    size_t availSpace;
    size_t recordCount;
    size_t fieldNum;
    size_t numFields;

    std::vector<std::pair<HeaderField, std::string>> headers;

    void readHeader();

   public:
    CsvBuffer(const size_t size = 4096, const char delim = ',');
    void read(std::istream& instream);
    bool unpack(std::string& str);

    std::string dump();
    size_t getAvailSpace();
    bool hasRecords();
    std::pair<HeaderField, std::string> getCurFieldHeader();
};

#endif  // CSVBUFFER_H
