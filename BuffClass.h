/* This file contains the buffer class. 
It has a read and unpack function. 
The functions are responsible for creating a buffer and
use a Place class to give them the desired data.  */

#ifndef DELTEXT_H
#define DELTEXT_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#ifndef FALSE
#define FALSE (0)
#define TRUE (1)
#endif
using namespace std;
class BuffClass
	// buffer which holds delimited text fields
{
public:
	BuffClass(char delim = ','); // construct with a maximum of maxFields
	void clear(); // clear fields from buffer
	bool read(istream& infile); //read the CSV file and put it inside the buffer	
	bool unpack(string& aStr); // extract the data from buffer one line at a time	
	void print(ostream&) const;
	int getLineCounter();
private:
	char delim;
	int counter;
	string buffer;
	unsigned long bufferSize = 0; // size of packed fields
	unsigned int maxByte = buffer.max_size(); // maximum buffer size 	
	int nextCharIndex = 0; // unpacking position in buffer
};

BuffClass::BuffClass(char del)
{
	delim = del;
	bufferSize = 0;
	nextCharIndex = 0;
}
int BuffClass::getLineCounter() {

	return counter;
}

// Clear the buffer
void BuffClass::clear()
{
	bufferSize = 0;
	nextCharIndex = 0;
}

// reads the data from CSV file
bool BuffClass::read(istream& infile)
{
	// clear buffer
	clear();

	// check if file can be opened	
	if (!infile)
	{
		cout << "No file exist..." << endl; return false;
	}

	// check buffer size

	string aLine;
	while (getline(infile, aLine))
	{
		bufferSize += aLine.length();
		counter += 1;
	}

	//first one good but after that buffersize is 0 
	if (bufferSize > maxByte)
	{
		cout << "Buffer overflow..." << endl; return false;
	}
	infile.clear();
	infile.seekg(0);
	// getting the new size of buffer
	getline(infile, buffer, (char)infile.eof());
	bufferSize = buffer.length();

	//buffer size is good	
	return true;
}
//get next line from buffer
bool BuffClass::unpack(string& aStr)
{
	if (nextCharIndex > bufferSize) return false;

	int len = -1; // length of unpacking string	
	int start = nextCharIndex;

	// look for delimiter
	for (int i = start; i < bufferSize; i++)
		if (buffer[i] == delim || buffer[i] == '\n')
		{
			len = i - start; break;
		}

	if (len == -1) { return false; } // if delim not found 
	// get the field
	nextCharIndex += len + 1;
	aStr = buffer.substr(start, len);
	aStr[len] = '\0';
	return true;
}

#endif


