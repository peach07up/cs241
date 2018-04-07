#include <dirent.h>
#include <stdio.h>
#include <string.h>

int dirlist(char*name) {
  struct dirent *dp;

  DIR* dirp = opendir(".");
  while ((dp = readdir(dirp)) != NULL) {
    puts(dp->d_name);
    if (!strcmp(dp->d_name, name)) {

        return 1; /* Found */
    }
  }
  closedir(dirp);
  return 0; /* Not Found */

}

int main() {
  return dirlist("prog.c");
}
