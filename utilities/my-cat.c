/*
CT30A3370_03.09.2018 Käyttöjärjestelmät ja systeemiohjelmointi
Harjoitustyö
Project 1: Unix Utilities
11.12.2018
Miikka Mättölä
---
Changelog:
2018-12-11 Initial version (MM)
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_BUFF 1024

void read_and_print_file(char *filename)
{
	FILE *file;
	char buffer[MAX_BUFF];
	
	/* Open file in read mode */
	file = fopen(filename, "r");
	
	if (!file)
	{
		printf("Can not open file\n");
		perror(filename);
		exit(EXIT_FAILURE);
	}
	
	while (fgets(buffer, sizeof(buffer), file))
	{
		printf("%s", buffer);
	}
	
	fclose(file);
}

int main(int argc, char *argv[]) {
	int i;
	
	if (argc < 2) {
		/* No files specified so exit silently */
		exit(EXIT_SUCCESS);
	} else {
		/* Iterate through argument list */
		for(i = 1; i < argc; i++) {
			/* Read file and print out its content */
			read_and_print_file(argv[i]);
		}
	}
	
	return EXIT_SUCCESS;
}
