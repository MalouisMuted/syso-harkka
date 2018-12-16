all : pzip punzip
pzip : pzip.o
	gcc -o pzip pzip.o -lm  -pthread
pzip.o : pzip.c
	gcc -g -c pzip.c -Wall -ansi -std=c99
punzip : punzip.o
	gcc -o punzip punzip.o
punzip.o : punzip.c
	gcc -g -c punzip.c -Wall -ansi -std=c99
clean :
	rm pzip.o punzip.o pzip punzip
