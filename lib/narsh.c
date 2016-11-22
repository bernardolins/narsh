#include "narsh.h"

FILE* open_file(const char* path) {
  FILE* file = fopen(path, "r");
  if(file == NULL) {
    fprintf(stderr, "%s\n", strerror(errno));
    exit(errno);
  }
  return(file);
}

off_t walk_file(FILE *file, int num_of_lines) {
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
