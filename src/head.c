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
    off_t last_byte_to_print = walk_file_from_beg(file, num_of_lines);
    print_line_from_beg(file, last_byte_to_print);
  }

  if(byte_set) {
    print_line_from_beg(file, num_of_bytes);
  }

  return(0);
}

