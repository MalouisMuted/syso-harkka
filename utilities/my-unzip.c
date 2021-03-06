/*
Author: Aleksi Kuznetsov
C-program for run-length-encoding/decoding
*/

#include <stdio.h> 
#include <stdlib.h> // For exit()
#include <stdint.h>

void uncompress_file(FILE *fp_in);

int main(int argc, char **argv) {
	if (argc == 1) {
		fprintf(stderr, "Not enough arguments.\n");
		exit(EXIT_FAILURE);
	}

	FILE *fptr_r; 

	// For loop for every argument that is file
	for (int i = 1; i < argc; i++) {
		fptr_r = fopen(argv[i], "rb"); 
		if (fptr_r == NULL) { 
			fprintf(stderr, "Cannot open file %s \n", argv[i]); 
			exit(EXIT_FAILURE); 
		} else {
			uncompress_file(fptr_r);
			fclose(fptr_r); 
		}
	}
	return EXIT_SUCCESS;
}

void uncompress_file(FILE *fp_in) {
	uint32_t count;
	int ch;

	while (1) {
		// Takes 4-byte integer and 1-byte char
		fread(&count, 1, 4, fp_in);
		fread(&ch, 1, 1, fp_in);

		if (feof(fp_in)) { 
         	break;
      	}

      	// Puts the right char count times into stdout
		for (int i = 0; i < count; i++) {
			putc(ch, stdout);
		}
	}
}
