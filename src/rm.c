#include "rm.h"

int main(int argc, char* argv[]) {
  int opt = 0;
  int non_opt_arguments = 0;

  char** file_names = initialize(argc);

  while(optind < argc) {
    if((opt = getopt(argc, argv, "f")) != -1) {
      switch(opt) {
        case 'f':
         force = 1;
         break;
      }
    } else {
      file_names[non_opt_arguments] = argv[optind];
      optind++;
      non_opt_arguments++;
    }
  }

  remove_from_list(file_names, non_opt_arguments);

  free(file_names);

  return(0);
}

char** initialize(int size) {
  char** strings = (char**)malloc(size * sizeof(char*));

  int i;
  for(i = 0; i < size; i++) {
    strings[i] = malloc((MAX_FILE_NAME + 1) * sizeof(char));
  }

  return strings;
}

void remove_from_list(char** files, int number_of_files) {
  int i;
  for(i = 0; i < number_of_files; i++) {
    if(!is_regular_file(files[i])) {
      if(force) {
        try_remove_one(files[i]);
      } else {
        fprintf(stderr, "rm: %s: is a directory\n", files[i]);
      }
    } else {
      try_remove_one(files[i]);
    }
  }
}

void try_remove_one(char* file) {
  if(remove(file) == -1) {
    fprintf(stderr, "%s: %s\n", file, strerror(errno));
  }
}

int is_regular_file(char *path) {
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);
}
