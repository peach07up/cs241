#include <stdlib.h>
#include <stdio.h>
#include "mini_valgrind.h"
int main() {
  // your tests here using malloc and free

  // Do NOT modify this line
  atexit(print_report);
  return 0;
}
