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
  off_t first_byte_to_print = walk_file_from_end(file, num_of_lines);
  print_line_from_end(file, first_byte_to_print);

  return(0);
}
