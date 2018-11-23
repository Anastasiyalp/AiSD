#!/bin/bash
g++ ./Source/Source.cpp -o Lab4
echo -e '_______\nTest 1:\n'
./Lab4 <./Tests/Test1.txt
echo -e '_______\nTest 2:\n'
./Lab4 <./Tests/Test2.txt
echo -e '_______\nTest 3:\n'
./Lab4 <./Tests/Test3.txt
echo -e '_______\nTest 4:\n'
./Lab4 <./Tests/Test4.txt
echo -e '_______\nTest 5:\n'
./Lab4 <./Tests/Test5.txt
echo -e '_______\nTest 6:\n'
./Lab4 <./Tests/Test6.txt
echo -e '_______\nTest 7:\n'
./Lab4 <./Tests/Test7.txt

