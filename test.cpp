#include <fstream>
#include <iostream>

#include "CsvBuffer.h"
#include "extremaTable.h"
int main(int argc, char const *argv[]) {
    // std::ifstream file("us_postal_codes.csv");
    std::ifstream file("lat_sort.csv");

    if(!file) {
        exit(0);
    }

    CsvBuffer buf;

    ExtremaTable test;
    int i = 0;

    while (!file.eof()) {

        buf.read(file);
        while (buf.recordCount > 0) {
            Place p;
            p.unpack(buf);
            test.update(p);
        }

    }
    file.close();

    // example of printing

    std::cout << "State\t"
              << "North\t"
              << "South\t"
              << "West\t"
              << "East\t" << std::endl;
    for (auto it : test.table) {
        std::cout << it.first << "\t"
                  << it.second.north.zip << "\t"
                  << it.second.south.zip << "\t"
                  << it.second.west.zip << "\t"
                  << it.second.east.zip << std::endl;
    }

    return 0;
}
