#include "ls.h"

int main(int argc, char* argv[]) {
  int opt = 0;
  char* dir_name = ".";

  while(optind < argc) {
    if((opt = getopt(argc, argv, "la")) != -1) {
      switch(opt) {
        case 'l':
         list = 1;
         break;
        case 'a':
         all = 1;
         break;
      }
    } else {
      dir_name = argv[optind];
      optind++;
    }
  }

  ls(dir_name);

  return(0);
}

void ls(char* dir_name) {
  DIR* dir;
  struct dirent* dir_entry;

  dir = opendir(dir_name);
  if (dir != NULL) {
    while((dir_entry = readdir(dir))) {
      if(dir_entry->d_name[0] == '.' && !all) continue;
      print_entry(dir_entry);
    }
    if(!list) printf("\n");
    closedir(dir);
  } else fprintf(stderr, "ls: %s: %s\n", dir_name, strerror(errno));
}

void print_entry(struct dirent* dir_entry) {
  char sep_char = '\t';
  if(list) sep_char = '\n';

  switch(dir_entry->d_type) {
    case DT_DIR:
      printf(DIR_COLOR "%-15.15s%c", dir_entry->d_name, sep_char);
      break;
    case DT_REG:
      printf(REG_COLOR "%-15.15s%c", dir_entry->d_name, sep_char);
      break;
    case DT_LNK:
      printf(LNK_COLOR "%-15.15s%c", dir_entry->d_name, sep_char);
      break;
    default:
      printf(UKN_COLOR "%-15.15s%c", dir_entry->d_name, sep_char);
      break;
  }
}
