#!/bin/bash

NAME=garden

/usr/bin/g++ -DEVAL -O2 -std=c++17 -o $NAME grader.cpp $NAME.cpp
