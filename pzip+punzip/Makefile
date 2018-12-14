all : pzip punzip
pzip : pzip.o
	gcc -o pzip pzip.o 
pzip.o : pzip.c
	gcc -c pzip.c -Wall -ansi -std=c99
punzip : punzip.o
	gcc -o punzip punzip.o 
punzip.o : punzip.c
	gcc -c punzip.c -Wall -ansi -std=c99
clean :
	rm pzip.o punzip.o pzip punzip
