#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int flag_set = 0; //flag not set

int walk_dir (const char *path, void (*func) (const char *));
void file_name(const char*);

int main(int argc, char* argv[]) {
  int modifier = S_IFREG;
  char* dirpath = ".";
  int opt = 0;

  while(optind <=  argc) {
    if((opt = getopt(argc, argv, "rdlbc:")) != -1) {
      if(flag_set == 0) {
        switch(opt) {
          case 'r':
           flag_set = 1;
           break;
          case 'd':
           flag_set = 1;
           modifier = S_IFDIR;
           break;
          case 'l':
           flag_set = 1;
           modifier = S_IFLNK;
           break;
          case 'b':
           flag_set = 1;
           modifier = S_IFBLK;
           break;
          case 'c':
           flag_set = 1;
           modifier = S_IFCHR;
           break;
        }
      }
    } else {
      dirpath = argv[optind-1];
      optind++;
    }
  }

  walk_dir(dirpath, &file_name);
}

void file_name(const char* full_path) {
  printf("%s\n", full_path);
}

int walk_dir (const char *path, void (*func) (const char *)) {
  DIR *dirp;
  struct dirent *dp;
  char *p, *full_path;
  int len;

  if ((dirp = opendir (path)) == NULL) return (-1);

  len = strlen (path);

  if ((full_path = malloc (len + NAME_MAX + 2)) == NULL) {
  closedir (dirp);
  return (-1);
  }

  memcpy (full_path, path, len);
  p = full_path + len; *p++ = '/';

  while ((dp = readdir (dirp)) != NULL) {
    if (strcmp (dp->d_name, ".") == 0 || strcmp (dp->d_name, "..") == 0) continue;
    strcpy (p, dp->d_name);
    (*func) (full_path);
  }

  free (full_path);
  closedir (dirp);

  return (0);
}
