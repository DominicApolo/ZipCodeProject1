#ifndef CSVBUFFER_H
#define CSVBUFFER_H

#include <istream>
#include <string>
#include <vector>

// idea adapted from https://stackoverflow.com/a/30338543
// used for tiny csv parsing state machine
enum class CSVState {
    QuotedField,
    UnquotedField,
    QuotedQuote
};

// contains the values that will be used to determine which value of the place class the field will be unpacked into
enum class HeaderField {
    ZipCode,
    PlaceName,
    State,
    County,
    Latitude,
    Longitude,
    Unknown
};

HeaderField getFieldType(std::string headerValue);

class CsvBuffer {
   private:
    const size_t maxSize;
    const char delim;

    std::string buffer;

    size_t curr;  // holds the position of the start of unprocessed fields
    size_t head;  // holds the position of the end of unprocessed fields

    size_t recordCount;  // number of records currently in the unprocessed part of the buffer
    size_t fieldNum;     // keeps track of how many fields of a record have been processed
    size_t numFields;    // number of fields in each record

    // first part holds the header type for use when unpacking,
    // second part holds the actual header value
    std::vector<std::pair<HeaderField, std::string>> headers;

    /**
     * @brief Reads through the first record in the file and extracts the fields for use as metadata.
     *
     * @pre headers is an empty vector and the buffer has had data read into it
     *
     * @post headers contains the pairs of header field types and the values of the header fields
     *       curr points to the first record
     *       numFields is equal to number of header fields found
     */
    void readHeader();

   public:
    CsvBuffer(const size_t size = 4096, const char delim = ',');

    /**
     * @brief Reads into the buffer getAvailSpace amount of data or to the end of the stream, whichever is smaller.
     *
     * @param[in] instream amount returned by getAvailSpace will be read from instream
     *
     * @pre instream is an open stream that contains data in a CSV format
     * @post buffer contains data to be unpacked from curr to head
     *       sets recordCount equal to number of records found while reading
     *
     */
    void read(std::istream& instream);

    /**
     * @brief Reads a field and puts it into a string
     *
     * @param[out] str the string that will hold the value of the field
     * @return true record has not had every field unpacked
     * @return false record has no more fields to unpack
     *
     * @pre curr is pointing to the start of a field
     *      str is an empty std::string
     *
     * @post str contains the value of the field
     *       curr is pointing to the start of the next field or the next record
     *
     */
    bool unpack(std::string& str);

    /**
     * @brief Performs the first read and extracts the headers.
     *
     * @param[in] instream stream to be read from
     *
     * @pre buffer is empty
     * @post headers contains the values returned by readHeader
     *       buffer contains raw data
     *       curr points to the start of the buffer
     *       head points to the end of the buffer or the amount of data read from the stream, whichever is smaller
     *       fieldNum is increased by one if the record contains more fields or is set to zero if the entire record has been read
     */
    void init(std::istream& instream);

    /**
     * @brief Calculates the amount of space between the curr and head pointers (the amount of space the can be reused).
     *
     * @pre None
     * @post returns the amount of space between the curr and head pointers
     *
     * @return the size of the processed data block
     */
    size_t getAvailSpace();

    /**
     * @brief Checks if there are records in the buffer yet to be unpacked
     *
     * @return true One or more records in the buffer
     * @return false Zero records in the buffer
     */
    bool hasRecords();

    /**
     * @brief Gets the type and value of the current field.
     *
     * @pre headers has been initialized
     *
     * @post returns a pair containing the HeaderField type and the string value of the current field's header
     *
     * @return std::pair<HeaderField, std::string>
     */
    std::pair<HeaderField, std::string> getCurFieldHeader();
};

#endif  // CSVBUFFER_H
