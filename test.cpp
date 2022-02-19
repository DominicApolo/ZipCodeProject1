#include <fstream>
#include <iostream>
#include <vector>

#include "CsvBuffer.h"
#include "extremaTable.h"

std::vector<std::string> unpackHeader(CsvBuffer& buf) {
    std::vector<std::string> headers;

    for (int i = 0; i < 6; i++) {
        std::string temp;
        buf.unpack(temp);
        std::cout << temp << std::endl;
        headers.push_back(temp);
    }
    return headers;
}

int main(int argc, char const* argv[]) {
    // check to see if there is a command line argument
    if (argc < 2) {
        std::cerr << "No input file given" << std::endl;
        exit(1);
    }

    std::ifstream file(argv[1]);

    if (!file) {
        exit(0);
    }

    CsvBuffer buf;

    ExtremaTable table;

    buf.read(file);
    auto headers = unpackHeader(buf);

    std::cout << buf.dump() << std::endl;

    while (!file.eof()) {
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
