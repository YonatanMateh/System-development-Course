complex:complex.o main.o
	gcc   -ansi -Wall  complex.o main.o complex.h -o complex -lm

main.o: main.c complex.h
	gcc   -ansi -pedantic -Wall  -c main.c

complex.o: complex.c complex.h
	gcc    -ansi -pedantic -Wall -c -lm complex.c 

