/*
Author: Aleksi Kuznetsov
C-program for run-length-encoding/decoding multithreaded
*/

#include <stdio.h>
#include <stdlib.h> // For exit() and malloc()
#include <stdint.h> // For uint_32
#include <limits.h> // For UINT_MAX
#include <sys/sysinfo.h> // For get_nprocs()
#include <sys/stat.h> // For fstat()
#include <sys/mman.h> // For mmap()
#include <fcntl.h>
#include <unistd.h> // For read()
#include <pthread.h> // For threads
#include <math.h> // For round()

typedef struct buffered_write {
    int repeat;
    char character;
    struct buffered_write *next;
} bw, *bw_ptr;

void compress_file(struct buffered_write *ptr) {
	while (ptr != NULL) {
		int count = ptr->repeat;
		char character = ptr->character;

		fwrite(&count, 1, 4, stdout);
		fwrite(&character, 1, 1, stdout);

        ptr = ptr->next;
    }
}

void read_from_file(struct buffered_write *ptr, char * adr, int length) {
	unsigned int count = 0;
	char ch = adr[0];

	for (int i = 0; i < length; i++) {
        char ch2 = adr[i];
        if (ch == ch2) {
        	count++;

        	ptr->repeat = count;
			ptr->character = ch;
		}
		if (ch != ch2) {
			ptr = ptr->next;
			count = 0;
		}
		ch = ch2;
    }

    if (count == UINT_MAX) {
    	ptr = ptr->next;
		count = 1;
    }
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Wrong amount of arguments.\n");
		exit(1);
	}

	// Get threads
	int num_of_threads = get_nprocs();
	struct stat buffer;
	int fd;
	char *addr;

	// Open file
	fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        exit(1);
    }
    // Get file size
    if (fstat(fd, &buffer) == -1) {
        exit(1);
    }
    // Memory map content
    addr = mmap(NULL, buffer.st_size, PROT_READ,
                       MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
        exit(1);
    }

    // Buffers
    bw_ptr buffers[num_of_threads];
    // Offset
	int offset = round(buffer.st_size / num_of_threads);

	for (int i = 0; i < num_of_threads; i++) {
		// Create struct for buffering input
		struct buffered_write *x_ptr, x;
    	x_ptr = &x;
    	buffers[i] = x_ptr;
    	// Write to buffer
		read_from_file(x_ptr, addr + offset * i, offset);
	}

	for (int i = 0; i < num_of_threads; i++) {
		// Compress from buffers
		compress_file(buffers[i]);
	}






/*
	// For loop for every argument that is file
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
	*/
	return 0;
}