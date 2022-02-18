#include "CsvBuffer.h"

// curr points to the start of unprocessed data
// head points to the end of unprocessed data
#include <iostream>
CsvBuffer::CsvBuffer(const size_t size, const char delim) {
    buffer.resize(size);
    this->delim = delim;
    maxSize = size;
    curr = 0;
    head = 0;
    recordCount = 0;
}

void CsvBuffer::read(std::istream& instream) {
    char c;
    // num of chars to read from the file
    long toRead = getAvailSpace();

    while (!instream.eof() && (toRead-- > 0)) {
        instream.get(c);
        // check for new line here
        if (c == '\n') {
            // TODO this is a hacky way to deal with the new line at the end of the file
            //      figure out a way to do this better?
            if (instream.peek() != '\n') {
                recordCount++;
            }
        }
        buffer[head] = c;
        // if we are past the end of the buffer, wrap back to the start
        head = (head + 1) % maxSize;
    }
}

void CsvBuffer::unpack(std::string& str) {
    while (true) {
        if (buffer[curr] == ',') {
            break;
        } else if (buffer[curr] == '\n') {
            recordCount--;
            break;
        } else {
            str.push_back(buffer[curr]);
        }
        // wrap around if necessary
        curr = (curr + 1) % maxSize;
    }
    // move past the delimiter, wrap around if necessary
    curr = (curr + 1) % maxSize;
}

size_t CsvBuffer::getAvailSpace() {
    size_t space = 0;
    if (head > curr) {
        // free space wraps around end of buffer, i.e. not contiguous
        space = maxSize - head;
        if (curr > 0) {
            space += (curr - 1);
        }
    } else if (head < curr) {
        // free space is nicely contiguous, but doesn't start at the beginning of the buffer
        space = curr - head;
    } else {
        // free space is contiguous and starts at the beginning of the buffer
        space += (curr - 1) % maxSize;
    }
    return space;
}

std::string CsvBuffer::dump() {
    return buffer;
}