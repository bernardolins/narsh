#include "tail.h"

#define BUFF_SIZE 4096


int main(int argc, char* argv[]) {
  int opt = 0;

  const char* file_name = argv[argc-1];

  while((opt = getopt(argc, argv, "nf:")) != -1) {
    switch(opt) {
      case 'n':
       num_of_lines = opt;
       break;

      case 'f':
       follow = 2;
       break;
    }
  }

  FILE* file = open_file(file_name);
  off_t pos = walk_file(file);
  print_line(file, pos);

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

void print_line(FILE *file, off_t pos) {
  fseek(file, pos, SEEK_SET);
  char c;
  while((c = fgetc(file)) != EOF) {
    putchar(c);
    fseek(file, 0, SEEK_CUR);
  }
}

off_t walk_file(FILE *file) {
  fseek(file, 0, SEEK_END);
  off_t pos = ftell(file);
  int current_byte;
  int end_offset_line = 0;

  while(end_offset_line < num_of_lines) {
    current_byte = fgetc(file); 
    if(current_byte == '\n') {
      end_offset_line++;
    }
    pos = ftell(file);
    fseek(file, -2, SEEK_CUR);
  }

  return pos;
}
