#include <dirent.h>
#include <stdio.h>
#include <string.h>

int dirlist(char*name) {
  struct dirent *dp;

  DIR* dirp = opendir(".");
  while ((dp = readdir(dirp)) != NULL) {
    puts(dp->d_name);
    printf("%d\n", dp->d_ino);
    if (!strcmp(dp->d_name, name)) {
 // RESOURCE LEAK!
        closedir(dirp);
        return 1; /* Found */
    }
  }
  closedir(dirp);
  return 0; /* Not Found */

}

int main() {
  return dirlist("prog.c");
}
