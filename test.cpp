#include <fstream>
#include <iostream>
#include <vector>

#include "CsvBuffer.h"
#include "extremaTable.h"
int main(int argc, char const *argv[]) {
    std::ifstream file("us_postal_codes.csv");

    CsvBuffer buf;

    ExtremaTable test;

    while (file.peek() != EOF) {
        buf.read(file);
        while (buf.recordCount > 0) {
            Place p;
            p.unpack(buf);
            p.print();
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    file.close();

    return 0;
}
