#include "headers/low_level.h"
#include "headers/screen.h"
#include "headers/util.h"

void main() {
  clear_screen();
  char str[20];
  char inp;
  char *s = " ";
  char *alphabet =
      "001234567890-=00qwertyuiop[]\n\\asdfghjkl;'000zxcvbnm,./000 ";

  print("type something\n");
  while (1) {
    char tmp = read_byte(0x60);

    if (tmp < 0) {
      s[0] = '\0';
      inp = '\0';
      continue;
    }

    if (alphabet[tmp] != inp) {
      inp = alphabet[tmp];
      switch (tmp) {
      case 72:
        print("up\n");
        break;
      case 75:
        print("left\n");
        break;
      case 80:
        print("down\n");
        break;
      case 77:
        print("right\n");
        break;
      default:
        s[0] = inp;
        print(s);
        // itos(str, tmp);
        // print(str);
        // print("\n");
      }
    }
  }
}
