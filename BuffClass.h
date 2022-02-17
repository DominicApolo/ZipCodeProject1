/* This file contains the buffer class.
It has a read and unpack function.
The functions are responsible for creating a buffer and
use a Place class to give them the desired data.  */
#pragma once
#ifndef DELTEXT_H
#define DELTEXT_H

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
// #ifndef FALSE
// #define FALSE (0)
// #define TRUE (1)
// #endif
using namespace std;
class BuffClass
// buffer which holds delimited text fields
{
   public:
    BuffClass(char delim = ',');  // construct with a maximum of maxFields
    void clear();                 // clear fields from buffer
    bool read(istream& infile);   // read the CSV file and put it inside the buffer
    bool unpack(string& aStr);    // extract the data from buffer one line at a time
    void print(ostream&) const;
    int getLineCounter();

   private:
    char delim;
    int counter;
    string buffer;
    unsigned long bufferSize = 0;              // size of packed fields
    unsigned int maxByte = buffer.max_size();  // maximum buffer size
    int nextCharIndex = 0;                     // unpacking position in buffer
};

#endif
