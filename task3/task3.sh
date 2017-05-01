#!/bin/bash

g++ -std=c++11 main.cpp -o main
mv main /usr/sbin
g++ -std=c++11 editing_rc_local.cpp -o editing_rc_local
./editing_rc_local

