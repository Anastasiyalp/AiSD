#!/bin/bash
cd ./Source
make
echo -e '_______\n\x1b[104mTest 1:\x1b[0m\n'
cat ../Tests/Tests1.txt
echo -e '_______\n\x1b[104mResult 1:\x1b[0m\n'
./Lab5 ../Tests/Tests1.txt

echo -e '_______\n\x1b[104mTest 2:\x1b[0m\n'
cat ../Tests/Tests2.txt
echo -e '_______\n\x1b[104mResult 2:\x1b[0m\n'
./Lab5 ../Tests/Tests2.txt

echo -e '_______\n\x1b[104mTest 3:\x1b[0m\n'
cat ../Tests/Tests3.txt
echo -e '_______\n\x1b[104mResult 3:\x1b[0m\n'
./Lab5 ../Tests/Tests3.txt

echo -e '_______\n\x1b[104mTest 4:\x1b[0m\n'
cat ../Tests/Tests4.txt
echo -e '_______\n\x1b[104mResult 4:\x1b[0m\n'
./Lab5 ../Tests/Tests4.txt

echo -e '_______\n\x1b[104mTest 5:\x1b[0m\n'
cat ../Tests/Tests5.txt
echo -e '_______\n\x1b[104mResult 5:\x1b[0m\n'
./Lab5 ../Tests/Tests5.txt

echo -e '_______\n\x1b[104mTest 6:\x1b[0m\n'
cat ../Tests/Tests6.txt
echo -e '_______\n\x1b[104mResult 6:\x1b[0m\n'
./Lab5 ../Tests/Tests6.txt

echo -e '_______\n\x1b[104mTest 7:\x1b[0m\n'
cat ../Tests/Tests7.txt
echo -e '_______\n\x1b[104mResult 7:\x1b[0m\n'
./Lab5 ../Tests/Tests7.txt

rm Lab5
cd ..
