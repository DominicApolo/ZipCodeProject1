#include "CsvBuffer.h"

#include <iostream>
#include <regex>
#include <cassert>

CsvBuffer::CsvBuffer(const size_t size, const char delim) : maxSize(size), delim(delim) {
    buffer.resize(size);
    curr = 0;
    head = 0;
    recordCount = 0;
}

void CsvBuffer::init(std::istream& instream) {
    read(instream);
    readHeader();
}

bool CsvBuffer::hasRecords() { return recordCount > 0; }

void CsvBuffer::read(std::istream& instream) {
    char c;
    bool inQuotes = false;
    // num of chars to read from the file
    long toRead = getAvailSpace();

    while (!instream.eof() && (toRead-- > 0)) {
        instream.get(c);
        // check for new line here
        if (c == '\n') {
            // TODO this is a hacky way to deal with the new line at the end of the file
            //      figure out a way to do this better?
            if (instream.peek() != '\n' && !inQuotes) {
                recordCount++;
            }
        } else if (c == '"') {
            inQuotes = !inQuotes;
        }
        buffer[head] = c;
        // if we are past the end of the buffer, wrap back to the start
        head = (head + 1) % maxSize;
    }
}

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
                    fieldNum++;
                } else if (c == '\n') {
                    fieldHasMore = false;
                    recordHasMore = false;
                    fieldNum = 0;
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
                    fieldNum++;
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

std::pair<HeaderField, std::string> CsvBuffer::getCurFieldHeader() {
    return headers[fieldNum];
}

HeaderField getFieldType(std::string headerValue) {
    std::regex zipCodePat("Zip\\s*Code");
    std::regex placeNamePat("Place\\s*Name");
    std::regex statePat("State");
    std::regex countyPat("County");
    std::regex latitudePat("Lat");
    std::regex longitudePat("Long");

    if (std::regex_search(headerValue, zipCodePat)) {
        return HeaderField::ZipCode;
    } else if (std::regex_search(headerValue, placeNamePat)) {
        return HeaderField::PlaceName;
    } else if (std::regex_search(headerValue, statePat)) {
        return HeaderField::State;
    } else if (std::regex_search(headerValue, countyPat)) {
        return HeaderField::County;
    } else if (std::regex_search(headerValue, latitudePat)) {
        return HeaderField::Latitude;
    } else if (std::regex_search(headerValue, longitudePat)) {
        return HeaderField::Longitude;
    } else {
        return HeaderField::Unknown;
    }
}

void CsvBuffer::readHeader() {
    bool more = true;
    while (more) {
        std::string temp;
        more = unpack(temp);
        headers.push_back({getFieldType(temp), temp});
    }
    numFields = headers.size();
}
