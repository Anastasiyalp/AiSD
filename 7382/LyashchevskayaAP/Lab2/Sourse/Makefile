all:app
	rm API.o Lab2.o

app: Lab2.o API.o
	gcc Lab2.o API.o -o Lab2

myk.o: Lab2.c API.h
	gcc -c Lab2.c

API.o: API.c API.h
	gcc -c  API.c
