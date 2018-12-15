/*
CT30A3370_03.09.2018 Käyttöjärjestelmät ja systeemiohjelmointi
Harjoitustyö
Project 2: Unix Shell
15.12.2018
Miikka Mättölä
---
Changelog:
2018-12-13 Initial version (MM)
2018-12-15 Path implementation (MM)
*/

/* This is needed for getline() */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_MAX 128

/* Define default path */
char *path[PATH_MAX] = {"/bin"};

int match(const char *a, const char *b) {
	/* Compare two strings */
	if (strcmp(a, b) == 0) {
		return 1;
	}
	
	return 0;
}

void set_path(char **list, int count) {
	int i;
	
	/* Clear old path */
	for (i = 0; i < PATH_MAX; i++) {
		path[0] = NULL;
	}
	
	if (count < 2) {
		/* Empty path */
		return;
	}
	
	/* Set and reserve memory for new path */
	for (i = 1; i < count; i++) {
		path[i - 1] = malloc(strlen(list[i]) + 1);
        strcpy(path[i - 1], list[i]);
	}
	
	/* Print out new path */
	printf("Path set:\n%s", path[0]);
	for (i = 1; i < count - 1; i++) {
		printf(":%s", path[i]);
	}
	printf("\n");
}

int parse_string(char* string, char* delim, char ***ret) {
    char **list;
    char *token;
    int i = 0;
	
	/* Reserve memory for list */
	list = (char**) malloc(sizeof(char*) * strlen(string));
	if (!list)
	{
		printf("Unable to allocate memory!\n");
		exit(EXIT_FAILURE);
	}
	
	printf("String: [%s]\n", string);
	
	/* Parse string */
	while ((token = strtok(string, delim)) != NULL) {
		list[i] = malloc(strlen(token) + 1);
		strcpy(list[i], token);
		printf("Part %d: %s\n", i, list[i]);
		i++;
		string = NULL;
    }
	
	printf("Number of parts: %d\n", i);
	
	list = realloc(list, sizeof(char*) * i);
	*ret = list;
	
    return i;
}

void process_command(char *command) {
	char	**arg_list;
	int		arg_count;
	char	*cmd;
	int		i;
	
	arg_count = parse_string(command, " ", &arg_list);
	
	/* Process built-in commands */
	cmd = strdup(arg_list[0]);
	
	if (match(cmd, "exit")) {
		if (arg_count == 1) {
			exit(EXIT_SUCCESS);
		} else {
			printf("Invalid command\n");
		}
	}
	else if (match(cmd, "cd")) {
		if (arg_count == 2) {
			/* Change directory */
		} else {
			printf("Invalid command\n");
		}
	}
	else if (match(cmd, "path")) {
		/* Set path */
		set_path(arg_list, arg_count);
	}
	else {
		/* Execute program */
	}
	
	/* Free memory */
	for (i = 0; i < arg_count; i++) {
		free(arg_list[i]);
	}
	free(arg_list);
}

void prompt(void) {
	char *line = NULL;
	size_t len = 0;
	ssize_t ret;
	
	printf("wish> ");
	
	while ((ret = getline(&line, &len, stdin)) != -1) {
		/* Remove newline char */
		line[strcspn(line, "\r\n")] = 0;
		/* Execute line if it is not empty */
		if (strlen(line) > 0) {
			process_command(line);
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
			process_command(line);
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
