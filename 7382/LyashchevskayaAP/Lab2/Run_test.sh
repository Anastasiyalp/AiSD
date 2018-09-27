#!/bin/bash
cd ./Sourse
make
cd ..
echo -e '_______\nTest 1:'
cat ./Tests/Test1.txt
echo -e '_______\nTesting:\n'
./Sourse/Lab2 < ./Tests/Test1.txt
echo -e ''
echo -e '_______\nTest 2:'
cat ./Tests/Test2.txt
echo -e '_______\nTesting:\n'
./Sourse/Lab2 < ./Tests/Test2.txt
echo -e ''
echo -e '_______\nTest 3:'
cat ./Tests/Test3.txt
echo -e '_______\nTesting:\n'
./Sourse/Lab2 < ./Tests/Test3.txt
echo -e ''
echo -e '_______\nTest 4:'
cat ./Tests/Test4.txt
echo -e '_______\nTesting:\n'
./Sourse/Lab2 < ./Tests/Test4.txt
echo -e ''
echo -e '_______\nTest 5:'
cat ./Tests/Test5.txt
echo -e '_______\nTesting:\n'
./Sourse/Lab2 < ./Tests/Test5.txt
echo -e ''
echo -e '_______\nTest 6:'
cat ./Tests/Test6.txt
echo -e '_______\nTesting:\n'
./Sourse/Lab2 < ./Tests/Test6.txt
echo -e ''
echo -e '_______\nTest 7:'
cat ./Tests/Test7.txt
echo -e '_______\nTesting:\n'
./Sourse/Lab2 < ./Tests/Test7.txt

