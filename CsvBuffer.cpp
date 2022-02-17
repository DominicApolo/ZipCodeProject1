#include "CsvBuffer.h"

#include <iostream>
// curr points to the start of unprocessed data
// head points to the end of unprocessed data

CsvBuffer::CsvBuffer(const size_t size) {
    buffer.resize(size);
    curr = 0;
    head = 0;
    maxSize = size;
    recordCount = 0;
}

void CsvBuffer::read(std::istream& instream) {
    char c;
    // num of chars to read from the file
    long toRead = 0;
    // if
    if (head > curr) {
        toRead = maxSize - head;
        toRead += (curr - 1) % 2048;
    } else if (head < curr) {
        toRead = curr - head;
    } else {
        toRead += (curr - 1) % 2048;
    }

    while (!instream.eof() && (toRead-- > 0)) {
        instream.get(c);
        // check for new line here
        if (c == '\n') {
            recordCount++;
        }
        buffer[head] = c;
        head = (head + 1) % maxSize;
    }
}

void CsvBuffer::unpack(std::string& str) {
    while (true) {
        if (buffer[curr] == ',') {
            break;
        }
        if (buffer[curr] == '\n') {
            recordCount--;
            break;
        }
        str.push_back(buffer[curr]);
        curr = (curr + 1) % maxSize;
    }

    curr = (curr + 1) % maxSize;
}