index:index.o main.o
	gcc   -ansi -Wall  index.o main.o index.h -o index 
main.o: main.c index.h
	gcc   -ansi -pedantic -Wall  -c main.c

index.o: index.c index.h
	gcc    -ansi -pedantic -Wall -c index.c 

