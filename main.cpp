#include <fstream>
#include <iostream>

#include "CsvBuffer.h"
#include "extremaTable.h"

/**
 * @brief Reads the csv file passed in as a commandline argument and outputs
 *  a formatted table of the northern, southern, eastern, and westernmost zipcodes in a state. 
 * 
 * @param argc Used to check if there is an input file
 * @param argv Contains the input file if given
 * @return int 
 */
int main(int argc, char const* argv[]) {
    // check to see if there is a command line argument
    if (argc < 2) {
        std::cerr << "No input file given" << std::endl;
        exit(1);
    }

    std::ifstream file(argv[1]);

    if (!file) {
        std::cerr << "Input file cannot be opened. (might not exist)" << std::endl;
        exit(1);
    }

    CsvBuffer buf;

    ExtremaTable table;

    buf.init(file);

    while (!file.eof() || buf.hasRecords()) {
        while (buf.hasRecords()) {
            Place p;
            p.unpack(buf);
            table.update(p);
        }
        buf.read(file);
    }
    file.close();

    // print table
    std::cout << table;

    return 0;
}
