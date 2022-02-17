#ifndef CSVBUFFER_H
#define CSVBUFFER_H

// #include "CircularBuffer.h"

#include <memory>
#include <string>
#include <istream>
class CsvBuffer {
   public:
    size_t curr;
    std::string buffer;
    size_t tail;
    size_t head;
    size_t emptySpace;
    size_t recordCount;
    size_t maxSize;

    // CircularBuffer buf;
   public:

    CsvBuffer(const size_t size = 2048);
    void read(std::istream& instream);
    void unpack(std::string& str);

    char operator[](size_t i);
    // char &operator[](size_t i);

    size_t getSpace() { return emptySpace; };
};

#endif  // CSVBUFFER_H
