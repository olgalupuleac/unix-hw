#!/bin/bash
sudo dd if=/dev/sda of=MBR bs=512 count=1 > /dev/null 2> /dev/null
g++ -std=c++11 main.cpp -o main
chmod +x main
./main
