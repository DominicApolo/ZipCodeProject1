#ifndef CSVBUFFER_H
#define CSVBUFFER_H

#include <string>
#include <istream>
class CsvBuffer {
   public:
    size_t curr;
    std::string buffer;
    size_t head;
    size_t availSpace;
    size_t recordCount;
    size_t maxSize;
    char delim;

   public:

    CsvBuffer(const size_t size = 2048, const char delim = ',');
    void read(std::istream& instream);
    void unpack(std::string& str);

    char operator[](size_t i);
    std::string dump();
    size_t getAvailSpace();
};

#endif  // CSVBUFFER_H
