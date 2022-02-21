#! /usr/bin/bash

rm ZipCode.out

g++ --std=c++17 -Wall -o ZipCode.out *.cpp

./ZipCode.out post_codes_w_headers.csv