#include "ls.h"

int main(int argc, char* argv[]) {
  int opt = 0;
  char* dir_name = ".";

  while(optind < argc) {
    if((opt = getopt(argc, argv, "la")) != -1) {
      switch(opt) {
        case 'l':
         list = 1;
         break;
        case 'a':
         all = 1;
         break;
      }
    } else {
      dir_name = argv[optind];
      optind++;
    }
  }

  ls(dir_name);

  return(0);
}

void ls(char* dir_name) {
  DIR* dir;
  struct dirent* dir_entry;

  dir = opendir(dir_name);
  if (dir != NULL) {
    while((dir_entry = readdir(dir))) {
      if(dir_entry->d_name[0] == '.' && !all) continue;
      print_entry(dir_entry);
    }
    if(!list) printf("\n");
    closedir(dir);
  } else fprintf(stderr, "ls: %s: %s\n", dir_name, strerror(errno));
}

void print_dirent_permissions(char* dirent_name) {
  struct stat filestat;
  if(stat(dirent_name, &filestat) < 0) {
    return;
  }
  
  struct passwd *pw = getpwuid(filestat.st_uid);
  struct group  *gr = getgrgid(filestat.st_gid);

  printf((S_ISDIR(filestat.st_mode))  ? "d" : "-");
  printf((filestat.st_mode & S_IRUSR) ? "r" : "-");
  printf((filestat.st_mode & S_IWUSR) ? "w" : "-");
  printf((filestat.st_mode & S_IXUSR) ? "x" : "-");
  printf((filestat.st_mode & S_IRGRP) ? "r" : "-");
  printf((filestat.st_mode & S_IWGRP) ? "w" : "-");
  printf((filestat.st_mode & S_IXGRP) ? "x" : "-");
  printf((filestat.st_mode & S_IROTH) ? "r" : "-");
  printf((filestat.st_mode & S_IWOTH) ? "w" : "-");
  printf((filestat.st_mode & S_IXOTH) ? "x" : "-"); 
  printf(" %s", pw->pw_name);
  printf(" %s", gr->gr_name);
  printf(" %5d", filestat.st_size);

  struct tm* tm = localtime(&filestat.st_mtime);

  printf(" %s %s %s:%s", format_month(tm->tm_mon), format_date_int(tm->tm_mday), format_date_int(tm->tm_hour), format_date_int(tm->tm_min));
}

char* format_date_int(int val) {
  char *result = (char*)malloc(2*sizeof(char));
  if(val > 9) {
    sprintf(result, "%d", val);
  } else {
    sprintf(result, "0%d", val);
  }
  return result; 
}

char* format_month(int month) {
  switch(month) {
    case 0:
      return "Jan";
      break;
    case 1:
      return "Feb";
      break;
    case 2:
      return "Mar";
      break;
    case 3:
      return "Apr";
      break;
    case 4:
      return "May";
      break;
    case 5:
      return "Jun";
      break;
    case 6:
      return "Jul";
      break;
    case 7:
      return "Aug";
      break;
    case 8:
      return "Sep";
      break;
    case 9:
      return "Oct";
      break;
    case 10:
      return "Nov";
      break;
    case 11:
      return "Dez";
      break;
    default:
      return "ERROR";
  }
}

void print_entry(struct dirent* dir_entry) {
  char sep_char = '\t';
  if(list) {
    sep_char = '\n';
    print_dirent_permissions(dir_entry->d_name);
    printf(" ");
  }

  switch(dir_entry->d_type) {
    case DT_DIR:
      printf(DIR_COLOR "%-15.15s%c" WHITE, dir_entry->d_name, sep_char);
      break;
    case DT_REG:
      printf(REG_COLOR "%-15.15s%c" WHITE, dir_entry->d_name, sep_char);
      break;
    case DT_LNK:
      printf(LNK_COLOR "%-15.15s%c" WHITE, dir_entry->d_name, sep_char);
      break;
    default:
      printf(UKN_COLOR "%-15.15s%c" WHITE, dir_entry->d_name, sep_char);
      break;
  }
}
