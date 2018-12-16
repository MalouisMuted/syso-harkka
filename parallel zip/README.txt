Käyttöjärjestelmät ja systeemiohjelmointi: Project 4: Parallel Zip

Parallel zipping works - or kind of. There are some memory leaks and the output is not reliable.
The idea was to take single input file and share it according to the number of threads (int num_of_threads = get_nprocs();) to chunks of memory.
After that I memorymapped (mmap()) it and made a buffer struct for each thread to write on.
Struct would have the character and number of times to be repeated. The structs would make up a linked list for iteration.
Every thread would begin their work on a different memory area.
After all the threads are done and joined, I would iterate all the buffers and write to stdout.
You will find the single thread version in the subfolder.

Sources:
http://man7.org/linux/man-pages/man2/mmap.2.html
http://pages.cs.wisc.edu/~remzi/OSTEP/
https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm
https://www.learn-c.org/en/Linked_lists

Repository:
https://github.com/MalouisMuted/syso-harkka/tree/master/pzip%2Bpunzip

How to run:
1. Run make in the folder

2. Use...
./pzip [input file] > [output file] or ./pzip [input file]
./punzip [input file] > [output file] or ./pzip [input file]

Author: Aleksi Kuznetsov
