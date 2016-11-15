#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int num_of_lines = 10;
int num_of_bytes = 0;

int line_set = 0;
int byte_set = 0;

int main(int argc, char* argv[]);
FILE* open_file(const char* path);
void print_line(FILE *file, off_t startline);
off_t walk_file(FILE *file);
