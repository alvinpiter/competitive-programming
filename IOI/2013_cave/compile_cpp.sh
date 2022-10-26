#!/bin/bash

NAME=cave

/usr/bin/g++ -DEVAL -O2 -o $NAME grader.c $NAME.cpp
