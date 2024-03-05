#include "headers/screen.h"
#include "headers/util.h"

void main() {
  printf("press a key to proceed\n");
  wait_until_key_pressed();
  printf("type smth: ");
  char s[30];
  gets(s);
  printf("%s\n", s);
}
