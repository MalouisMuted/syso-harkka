/*
Author: Aleksi Kuznetsov
C-program for run-length-encoding/decoding
*/

#include <stdio.h> 
#include <stdlib.h> // For exit()
#include <stdint.h>

#define FOUR_BYTE_MAX 4294967295

void compress_file(FILE *fp_in);

int main(int argc, char **argv) {
	if (argc == 1) {
		fprintf(stderr, "Not enough arguments.\n");
		exit(EXIT_FAILURE);
	}

	FILE *fptr_r;

	// For loop for every argument that is file
	for (int i = 1; i < argc; i++) {
		fptr_r = fopen(argv[i], "r"); 
		if (fptr_r == NULL) { 
			fprintf(stderr, "Cannot open file %s \n", argv[i]); 
			exit(EXIT_FAILURE);
		} else {
			compress_file(fptr_r);
			fclose(fptr_r); 
		}
	}
	return EXIT_SUCCESS;
}

void compress_file(FILE *fp_in) {
	uint32_t count;
	int ch = getc(fp_in);
	int ch2 = ch;
	while (ch2 != EOF) {
		// Loop until we hit FOUR_BYTE_MAX or character changes
		for (count = 0; ch2 == ch && count < FOUR_BYTE_MAX; count++) {
				ch2 = getc(fp_in);
			}
		// Write 4-byte integer and 1-byte char into stdout
		fwrite(&count, 1, 4, stdout);
		fwrite(&ch, 1, 1, stdout);
		ch = ch2;
	}
}
