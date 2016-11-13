#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>


#define MAX_FILE_NAME 1024

int force = 0;

int main(int argc, char* argv[]);
char** initialize(int size);
void remove_from_list(char** files, int number_of_files);
void try_remove_one(char* file);
int is_regular_file(char* path);
