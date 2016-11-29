#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define REG_COLOR "\x1B[37m" //white
#define DIR_COLOR "\x1B[34m" //blue
#define LNK_COLOR "\x1B[32m" //green
#define UKN_COLOR "\x1B[31m" //red
#define WHITE "\x1B[37m" //red

int list = 0;
int all = 0;

int main(int argc, char* argv[]);
void print_entry(struct dirent* dir_entry);
void ls(char* dir_name);
void print_file_permissions(char* filename);

char* format_month(int month);
char* format_date_int(int val);
