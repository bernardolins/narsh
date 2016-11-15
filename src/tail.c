#include "tail.h"

int main(int argc, char* argv[]) {
  int opt = 0;

  const char* file_name = argv[argc-1];

  while(optind < argc) {
    if((opt = getopt(argc, argv, "fn:")) != -1) {
      switch(opt) {
        case 'n':
         num_of_lines = atoi(optarg);
         break;

        case 'f':
         follow = 1;
         break;
      }
    } else {
      file_name = argv[optind];
      optind++;
    }
  }

  FILE* file = open_file(file_name);
  off_t first_byte_to_print = walk_file(file);
  print_line(file, first_byte_to_print);

  return(0);
}

FILE* open_file(const char* path) {
  FILE* file = fopen(path, "r");
  if(file == NULL) {
    fprintf(stderr, "%s\n", strerror(errno));
    exit(errno);
  }
  return(file);
}

off_t walk_file(FILE *file) {
  fseek(file, 0, SEEK_END);
  off_t pos = ftell(file);
  int current_byte;
  int num_of_lines_from_end = 0;

  while(num_of_lines_from_end < num_of_lines) {
    current_byte = fgetc(file);
    if(current_byte == '\n') {
      num_of_lines_from_end++;
    }
    pos = ftell(file);
    fseek(file, -2, SEEK_CUR);
    if(pos == 1) return 0;
  }

  return pos;
}

void print_line(FILE *file, off_t initial_pos) {
  fseek(file, initial_pos, SEEK_SET);
  char c;
  while((c = fgetc(file)) != EOF) {
    putchar(c);
    fseek(file, 0, SEEK_CUR);
  }
}
