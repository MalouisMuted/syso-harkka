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

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int has_string(char *haystack, char *needle) {
	char *ret;
	
	/* Search for needle in the haystack */
	ret = strstr(haystack, needle);
	
	if (!ret) {
		/* String not found (NULL) */
		return 0;
	} else {
		/* String was found */
		return 1;
	}
}

void read_file_and_search(char *filename, char *keyword) {
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	ssize_t ret;
	
	/* Open file in read mode */
	file = fopen(filename, "r");
	
	if (!file) {
		printf("Can not open file\n");
		perror(filename);
		exit(EXIT_FAILURE);
	}
	
	while ((ret = getline(&line, &len, file)) != -1) {
		/* Search for keyword in the line */
		if (has_string(line, keyword)) {
			printf("%s", line);
		}
	}
	
	free(line);
	fclose(file);
}

void read_stdin_and_search(char *keyword) {
	char *line = NULL;
	size_t len = 0;
	ssize_t ret;
	
	while ((ret = getline(&line, &len, stdin)) != -1) {
		/* Search for keyword in the line */
		if (has_string(line, keyword)) {
			printf("%s", line);
		}
	}
	
	free(line);
}

int main(int argc, char *argv[]) {
	int i;
	
	if (argc < 2) {
		/* No files specified so exit */
		printf("my-grep search_term file [...]\n");
		exit(EXIT_FAILURE);
	} else if (argc == 2) {
		/* Read from standard input */
		read_stdin_and_search(argv[1]);
	} else {
		/* Iterate through argument list */
		for(i = 2; i < argc; i++) {
			/* Read file and search for keyword */
			read_file_and_search(argv[i], argv[1]);
		}
	}
	
	return EXIT_SUCCESS;
}
