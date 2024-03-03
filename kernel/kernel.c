#include "headers/low_level.h"
#include "headers/screen.h"
#include "headers/util.h"

void main() {
  clear_screen();
  __asm__("hlt");

  // char s[32];
  // while (1) {
  //   getns(s, 30);
  //   printf("%s\n", s);
  // }

  // while (1) {
  //   char tmp = read_byte(0x60);
  //
  //   if (tmp < 0) {
  //     s[0] = '\0';
  //     inp = '\0';
  //     continue;
  //   }
  //
  //   if (alphabet[tmp] != inp) {
  //     inp = alphabet[tmp];
  //     switch (tmp) {
  //     case 72:
  //       print("up\n");
  //       break;
  //     case 75:
  //       print("left\n");
  //       break;
  //     case 80:
  //       print("down\n");
  //       break;
  //     case 77:
  //       print("right\n");
  //       break;
  //     default:
  //       s[0] = inp;
  //       print(s);
  //       // itos(str, tmp);
  //       // print(str);
  //       // print("\n");
  //     }
  //   }
  // }
}
