
#include <stdio.h> 
#include <stdlib.h> // For exit()
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <limits.h>

void uncompress_file(FILE *fp_in, FILE *fp_out);

int main(int argc, char **argv) {
	if (argc < 3) {
		printf("Not enough arguments.\n");
		exit(1);
	}

	FILE *fptr_w; 
	char file_r[100], file_w[100];
	// Last argv is target file
	strcpy(file_w, argv[argc - 1]);

	fptr_w = fopen(file_w, "w"); 
	if (fptr_w == NULL) { 
		printf("Cannot open file %s \n", file_w); 
		exit(1); 
	}

	for (int i = 1; i < argc - 1; i++) {
		// Open file for reading
		FILE *fptr_r;
		strcpy(file_r, argv[i]);
		fptr_r = fopen(file_r, "rb"); 
		if (fptr_r == NULL) { 
			printf("Cannot open file %s \n", file_r); 
			exit(1); 
		} else {
			printf("uncompressing file %s\n", file_r);
			uncompress_file(fptr_r, fptr_w);
			fclose(fptr_r); 
		}
	}

	fclose(fptr_w); 
	return 0;
}

void uncompress_file(FILE *fp_in, FILE *fp_out) {
	int count, ch, ch2;

	for (count = 0; ch2 != EOF; count = 0) {
		ch = getc(fp_in);   // grab first byte
		ch2 = getc(fp_in);  // grab second byte
		// write the bytes
		do {
			putc(ch2, fp_out);
			count++;
		} while (count < ch);
	}
}
