
#include <stdio.h> 
#include <stdlib.h> // For exit()
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <limits.h>

void compress_file(FILE *fp_in);

int main(int argc, char **argv) {
	if (argc == 1) {
		fprintf(stderr, "Not enough arguments.\n");
		exit(1);
	}

	FILE *fptr_r;

	for (int i = 1; i < argc; i++) {
		fptr_r = fopen(argv[i], "r"); 
		if (fptr_r == NULL) { 
			fprintf(stderr, "Cannot open file %s \n", argv[i]); 
			exit(1); 
		} else {
			compress_file(fptr_r);
			fclose(fptr_r); 
		}
	}
	return 0;
}

void compress_file(FILE *fp_in) {
	unsigned int count;
	int ch = getc(fp_in);
	int ch2 = ch;
	while (ch2 != EOF) {
		for (count = 0; ch2 == ch && count < UINT_MAX; count++) {
				ch2 = getc(fp_in);
			}
		fwrite(&count, 1, 4, stdout);
		fwrite(&ch, 1, 1, stdout);
		ch = ch2;
	}
}
