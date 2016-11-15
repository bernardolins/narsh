#include "head.h"

int main(int argc, char* argv[]) {
  int opt = 0;

  const char* file_name = argv[argc-1];

  while(optind < argc) {
    if((opt = getopt(argc, argv, "c:n:")) != -1) {
      switch(opt) {
        case 'n':
          line_set = 1;
          num_of_lines = atoi(optarg);
          break;
        case 'c':
          byte_set = 1;
          num_of_bytes = atoi(optarg);
          break;
      }
    } else {
      file_name = argv[optind];
      optind++;
    }
  }

  if(line_set && byte_set) {
    fprintf(stderr, "head: can't combine line and byte counts\n");
    exit(-1);
  }

  if(byte_set && num_of_bytes <= 0) {
    fprintf(stderr, "head: illegal byte count -- %s\n", file_name);
    exit(-1);
  }

  FILE* file = open_file(file_name);
  if(line_set) {
    off_t last_byte_to_print = walk_file(file);
    print_line(file, last_byte_to_print);
  }

  if(byte_set) {
    print_line(file, num_of_bytes);
  }

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
  fseek(file, 0, SEEK_SET);
  off_t pos = ftell(file);
  int current_byte;
  int num_of_lines_from_beginning = 0;

  while(num_of_lines_from_beginning < num_of_lines) {
    current_byte = fgetc(file);
    if(current_byte == '\n') {
      num_of_lines_from_beginning++;
    } else if(current_byte == EOF) break;
    pos = ftell(file);
    fseek(file, 0, SEEK_CUR);
  }

  return pos;
}

void print_line(FILE *file, off_t final_pos) {
  fseek(file, 0, SEEK_SET);
  off_t  pos = ftell(file);
  char c;
  while(pos != final_pos) {
    c = fgetc(file);
    pos = ftell(file);
    putchar(c);
    fseek(file, 0, SEEK_CUR);
  }
}
