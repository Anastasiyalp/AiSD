#!/bin/bash
g++ ./Source/Lab3.cpp -o Lab3
echo -e '_______\nTest 1:\n'
./Lab3 ./Tests/Names1.txt ./Tests/Connections1.txt
echo -e '_______\nTest 2:\n'
./Lab3 ./Tests/Names2.txt ./Tests/Connections2.txt
echo -e '_______\nTest 3:\n'
./Lab3 ./Tests/Names3.txt ./Tests/Connections3.txt
echo -e '_______\nTest 4:\n'
./Lab3 ./Tests/Names4.txt ./Tests/Connections4.txt
echo -e '_______\nTest 5:\n'
./Lab3 ./Tests/Names5.txt ./Tests/Connections5.txt
echo -e '_______\nTest 6:\n'
./Lab3 ./Tests/Names6.txt ./Tests/Connections6.txt
