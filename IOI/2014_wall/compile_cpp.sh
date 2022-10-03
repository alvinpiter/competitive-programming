#!/bin/bash

NAME=wall

/usr/bin/g++ -DEVAL -O2 -std=c++11 -o $NAME grader.cpp $NAME.cpp
