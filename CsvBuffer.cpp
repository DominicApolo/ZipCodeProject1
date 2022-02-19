#include "CsvBuffer.h"

// curr points to the start of unprocessed data
// head points to the end of unprocessed data
#include <iostream>

/**
 * @brief Construct a new Csv Buffer:: Csv Buffer object
 *
 * @param size
 * @param delim
 */
CsvBuffer::CsvBuffer(const size_t size, const char delim) : maxSize(size), delim(delim) {
    buffer.resize(size);
    curr = 0;
    head = 0;
    recordCount = 0;
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
bool CsvBuffer::hasRecords() { return recordCount > 0; }

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

/**
 * @brief
 *
 * @param str
 * @return true
 * @return false
 */
bool CsvBuffer::unpack(std::string& str) {
    auto state = CSVState::UnquotedField;  // assume field is not quoted by default

    bool fieldHasMore = true;
    bool recordHasMore = true;
    while (fieldHasMore) {
        char c = buffer[curr];
        switch (state) {
            case CSVState::UnquotedField:
                if (c == delim) {
                    fieldHasMore = false;
                } else if (c == '\n') {
                    fieldHasMore = false;
                    recordHasMore = false;
                    recordCount--;
                } else if (c == '"') {
                    state = CSVState::QuotedField;
                } else {
                    str.push_back(c);
                }
                break;
            case CSVState::QuotedField:
                if (c == '"') {
                    state = CSVState::QuotedQuote;
                } else {
                    str.push_back(c);
                }
                break;
            case CSVState::QuotedQuote:
                if (c == delim) {
                    fieldHasMore = false;
                } else if (c == '"') {
                    str.push_back(c);
                    state = CSVState::QuotedField;
                } else {
                    state = CSVState::UnquotedField;
                }
                break;
        }
        curr = (curr + 1) % maxSize;
    }
    return recordHasMore;
}

/**
 * @brief
 *
 * @return size_t
 */
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

/**
 * @brief
 *
 * @return std::string
 */
std::string CsvBuffer::dump() {
    return buffer;
}