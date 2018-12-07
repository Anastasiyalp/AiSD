all: hello clean

hello: bst4.o bst_implementation.o
	g++ bst4.o bst_implementation.o -o Lab5

bst_implementation.o: bst_implementation.cpp BStree.h
	g++ -c bst_implementation.cpp

bst4.o: bst4.cpp BStree.h
	g++ -c bst4.cpp

clean:
	rm -rf *.o
