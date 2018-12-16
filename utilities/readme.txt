unix utilities readme

Build:
make all (or build separately)
make my-cat
make my-grep
make my-zip
make my-unzip

[my-cat]

This utility reads a file (or multiple files) and prints out file contents.

Run:
./my-cat filename(s)
./my-cat file1.txt file2.txt [...]

[my-grep]

This utility scans files or the standard input (stdin) for a search term.
If a matching line is found, it is printed out.

Run:
./my-grep search_term filename(s)
./my-grep search_term file1.txt file2.txt [...]
./my-grep search_term

In the last example standard input (stdin) is used.

[my-zip]

This utility is used to compress files with run-length encoding (RLE).

Run:
./my-zip filename(s)
./my-zip file1.txt
./my-zip file1.txt > out.file

By default, output is written to standard output.
Output redirection can be used to save the output stream in a file.

[my-unzip]

This utility is used to decompress files processed by my-zip.

Run:
./my-unzip filename(s)
./my-unzip file1.txt
./my-unzip file1.txt > out.file

By default, output is written to standard output.
Output redirection can be used to save the output stream in a file.

Authors:
Miikka Mättölä
Aleksi Kuznetsov

References:
http://man7.org/linux/man-pages/man3/getline.3.html
http://man7.org/linux/man-pages/man3/strstr.3.html
https://www.gnu.org/software/libc/manual/html_node/Exit-Status.html
https://www.tutorialspoint.com/c_standard_library/c_function_fgets.htm
https://www.tutorialspoint.com/c_standard_library/c_function_strstr.htm
https://www.tutorialspoint.com/cprogramming/c_error_handling.htm
