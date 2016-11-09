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
  walk_file(file);


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

void print_line(FILE *file, off_t startline) {
  int fd;
  fd = fileno(file);
  int nread;
  char buffer[BUFF_SIZE];
  lseek(fd,(startline + 1),SEEK_SET);
  while((nread= read(fd,buffer,BUFF_SIZE)) > 0) {
    write(STDOUT_FILENO, buffer, nread);
  }
}

void walk_file(FILE *file) {
  off_t fposition;
  fseek(file,0,SEEK_END);
  fposition = ftell(file);
  off_t index = fposition;
  off_t end = fposition;
  long countlines = 0;
  char cbyte;

  for(index; index >= 0; index --) {
    cbyte= fgetc(file);
    if (cbyte == '\n' && (end - index) > 1) {
      countlines ++;
      if(countlines == num_of_lines) {
        break;
      }
    }
    fposition--;
    fseek(file,fposition,SEEK_SET);
  }
  print_line(file, fposition);
  fclose(file);
}
