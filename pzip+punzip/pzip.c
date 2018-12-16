/*
Author: Aleksi Kuznetsov
C-program for run-length-encoding/decoding multithreaded
*/

#include <stdio.h>
#include <stdlib.h> // exit() and malloc()
#include <stdint.h> // uint_32
#include <limits.h> // UINT_MAX
#include <sys/sysinfo.h> // get_nprocs()
#include <sys/stat.h> // fstat()
#include <sys/mman.h> // mmap()
#include <fcntl.h> // open()
#include <unistd.h> // read()
#include <pthread.h> // threads
#include <math.h> // round()

// Struct to store a character and how many times it repeats
typedef struct buffered_write {
    int repeat;
    char character;
    struct buffered_write *next;
} bw, *bw_ptr;

// Struct for arg to threads
typedef struct _myarg_t {
	bw_ptr ptr;
	char * adr;
	int length;
} myarg_t;

void compress_file(bw_ptr ptr) {
	while (ptr != NULL) {
		int count = ptr->repeat;
		char character = ptr->character;

		fwrite(&count, 1, 4, stdout);
		fwrite(&character, 1, 1, stdout);

        ptr = ptr->next;
    }
}

void freeList(bw_ptr root) {
	bw_ptr tmp;

	while (root != NULL) {
		tmp = root;
		root = root->next;
		free(tmp);
	}
}

void read_from_file(bw_ptr ptr, char * adr, int length) {
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
			ptr->next = malloc(sizeof(bw));
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

void *mythread(void *arg) {
	myarg_t *m = (myarg_t *)arg;
	read_from_file(m->ptr, m->adr, m->length);
	return NULL;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Wrong amount of arguments.\n");
		exit(1);
	}

	// Get threads, init file stats and addresses
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
    // Memory map the file contents
    addr = mmap(NULL, buffer.st_size, PROT_READ,
                       MAP_PRIVATE, fd, 0);
    if (addr == MAP_FAILED) {
        exit(1);
    }

    // Buffers
    bw_ptr buffers[num_of_threads];
    // Offset so we can divide the workload to several threads
	int offset = round(buffer.st_size / num_of_threads);
	// Thread container
	pthread_t thread_container[num_of_threads];

	for (int i = 0; i < num_of_threads; i++) {
		// Create struct for buffering input
		bw *x_ptr = NULL;
		x_ptr = malloc(sizeof(bw));
		if (x_ptr == NULL) {
			exit(1);
		}
		// Here we add to struct pointer array so we can iterate it later when writing output
    	buffers[i] = x_ptr;

    	// Write to the buffer and add to thread_container
    	pthread_t p;
		myarg_t args;
		args.ptr = x_ptr;
		args.adr = addr + offset * i;
		args.length = offset;
		thread_container[i] = p;
		pthread_create(&p, NULL, mythread, &args);
	}

	// Join threads
	for (int i = 0; i < num_of_threads; i++) {
		pthread_join(thread_container[i], NULL);
	}

	// Collect the data and write to stdout
	for (int i = 0; i < num_of_threads; i++) {
		compress_file(buffers[i]);
	}

	// Free memory from linked list and mmap under
	for (int i = 0; i < num_of_threads; i++) {
		freeList(buffers[i]);
	}

	munmap(addr, buffer.st_size);

	return 0;
}