#!/bin/bash

problem=molecules

g++ -O2 -std=c++17 -o $problem grader.cpp $problem.cpp
