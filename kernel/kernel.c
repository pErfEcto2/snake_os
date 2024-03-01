#include "headers/low_level.h"
#include "headers/screen.h"
#include "headers/util.h"

void main() {
  clear_screen();
  char str[20];
  char inp;
  char *s = " ";

  while (1) {
    char tmp = read_byte(0x60);

    if (tmp < 0) {
      s[0] = '\0';
      inp = '\0';
    } else if (tmp != inp) {
      inp = tmp;
      switch (inp) {
      case 16:
        s[0] = 'q';
        break;
      }
      print(s);
    }
  }
}
