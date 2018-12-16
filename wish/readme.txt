wish shell readme

Build:
make wish (or make all)

Run:
./wish			interactive mode
./wish filename		batch mode

wish shell supports the following built-in commands: cd, path, exit.

command		arguments		feature				description
cd		[1]			Change directories		This takes exactly one argument: path.
path		[0-n]			Set path variable		Path variable is used to locate program binaries.
exit		[0]			Exit shell			Self-explanatory. Does not take any arguments.

Output redirection is supported using the ">" character followed by a filename.
Example: cat file.txt > other.txt

Author:
Miikka Mättölä

References:
http://man7.org/linux/man-pages/man2/chdir.2.html
http://man7.org/linux/man-pages/man2/fork.2.html
http://man7.org/linux/man-pages/man2/getcwd.2.html
http://man7.org/linux/man-pages/man2/open.2.html
http://man7.org/linux/man-pages/man2/waitpid.2.html
http://man7.org/linux/man-pages/man3/exec.3.html
https://stackoverflow.com/questions/13293226/initializing-array-element-to-null
https://stackoverflow.com/questions/21350952/c-alternative-to-phps-explode-function
https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
https://stackoverflow.com/questions/8465006/how-do-i-concatenate-two-strings-in-c
https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/dup2.html
https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
