all : my-zip my-unzip
my-zip : my-zip.o
	gcc -o my-zip my-zip.o 
my-zip.o : my-zip.c
	gcc -c my-zip.c -Wall -ansi -std=c99
my-unzip : my-unzip.o
	gcc -o my-unzip my-unzip.o 
my-unzip.o : my-unzip.c
	gcc -c my-unzip.c -Wall -ansi -std=c99
clean :
	rm my-zip.o my-unzip.o my-zip my-unzip
