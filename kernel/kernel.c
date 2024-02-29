#include "headers/screen.h"

void main() {
  clear_screen();
  char *s = "a\n";

  for (char i = 'a'; i < 'a' + ROWS - 1; i++) {
    *s = i;
    print(s);
  }

  print("test");
  print("\nTEST");
}
