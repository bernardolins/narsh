#include "rm.h"

int main(int argc, char* argv[]) {
  int opt = 0;

  const char* file_name = argv[argc-1];

  while(optind < argc) {
    if((opt = getopt(argc, argv, "f")) != -1) {
      switch(opt) {
        case 'f':
         force = 1;
         break;
      }
    } else {
      file_name = argv[optind];
      optind++;
    }
  }

  if(remove(file_name) == -1) {
    fprintf(stderr, "%s\n", strerror(errno));
  }

  return(0);
}
