/*
CT30A3370_03.09.2018 Käyttöjärjestelmät ja systeemiohjelmointi
Harjoitustyö
Project 2: Unix Shell
13.12.2018
Miikka Mättölä
---
Changelog:
2018-12-13 Initial version (MM)
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARG_MAX 1024
#define ARG_SIZE 1024

void execute(char *command) {
	char *token;
	const char *delim = " ";
	char argument[ARG_MAX][ARG_SIZE];
	int count;
	
	printf("Command: %s\n", command);
	
	/* Parse command */
	token = strtok(command, delim);
	strcpy(argument[0], token);
	count = 1;
	printf("Argument %d: %s\n", count, token);
	
	while ((token = strtok(NULL, delim)) != NULL) {
		count++;
		strcpy(argument[count], token);
		printf("Argument %d: %s\n", count, token);
		
		printf("Number of arguments: %d\n", count);
		
		/* Process built-in commands */
		switch (argument[0]) {
			case 'exit':
				if (count == 1) {
					exit(EXIT_SUCCESS);
				} else {
					printf("Invalid command\n");
				}
				break;
			case 'cd':
				if (count == 2) {
					/* Change directory */
				} else {
					printf("Invalid command\n");
				}
				break;
			case 'path':
				/* Set path */
				break;
			default:
				/* Execute program */
				break;
		}
	}
}

void prompt() {
	char *line = NULL;
	size_t len = 0;
	ssize_t ret;
	
	printf("wish> ");
	
	while ((ret = getline(&line, &len, stdin)) != -1) {
		/* Remove newline char */
		line[strcspn(line, "\r\n")] = 0;
		/* Execute line if it is not empty */
		if (strlen(line) > 0) {
			execute(line);
		}
		printf("wish> ");
	}
	
	free(line);
}

void read_file(char *filename) {
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
		/* Remove newline char */
		line[strcspn(line, "\r\n")] = 0;
		/* Execute line if it is not empty */
		if (strlen(line) > 0) {
			execute(line);
		}
	}
	
	free(line);
	fclose(file);
}

int main(int argc, char *argv[]) {
	
	if (argc < 2) {
		/* Interactive mode */
		prompt();
	} else if (argc == 2) {
		/* Batch mode */
		read_file(argv[1]);
	} else {
		/* Too many arguments */
		printf("Too many arguments\n");
		exit(EXIT_FAILURE);
	}
	
	return EXIT_SUCCESS;
}
