#pragma once

#define REG_KEYBOARD_DATA 0x60

struct KeysPressed {
  char W;
  char A;
  char S;
  char D;
  char Y;
  char N;
};

void init_keyboard();
