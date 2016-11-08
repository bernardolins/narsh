#include "tail.h"

int main(int argc, char* argv[]) {
  int opt = 0;

  while((opt = getopt(argc, argv, "n")) != -1) {
    switch(opt) {
      case 'n':
       num_of_lines = opt;
       break;

      case 'f':
       follow = 1;
       break;
    }
  }

  printf("%d\n", num_of_lines);

  return(0);
}
