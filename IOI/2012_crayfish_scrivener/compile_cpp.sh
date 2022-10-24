#!/bin/bash

NAME=scrivener

/usr/bin/g++ -DEVAL -Wall -O2 -o $NAME grader.cpp $NAME.cpp
