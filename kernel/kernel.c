#include "headers/keyboard.h"
#include "headers/screen.h"
#include "headers/util.h"

typedef struct Vec2 {
  int x;
  int y;
} Vec2;

extern struct KeysPressed KeysPressed;
void main() {
  clear_screen();

  srand(0);
  while (1) {
    printf("%d\n", rand());
    sleep(25);
  }

  // printf("hi, do u wanna play a snake?\nActually, u have no choice\n"
  //        "Controls on wasd\nPress any key to start\n");
  // wait_until_key_pressed();
  // clear_screen();
  //
  // Vec2 apple;
  // Vec2 snake[ROWS * COLUMNS];
}
