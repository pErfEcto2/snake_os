#include "../headers/keyboard.h"
#include "../headers/low_level.h"
#include "../headers/screen.h"
#include "../headers/util.h"
#include "../idt/idt.h"

volatile char last_pressed;
char *alphabet = "001234567890-=\b0qwertyuiop[]\n\\asdfghjkl;'000zxcvbnm,./"
                 "000 0000000000000000000000000000000000000000000000000000";

struct KeysPressed KeysPressed;

void on_irq1(struct InterruptRegisters *regs) {
  char tmp = read_byte(REG_KEYBOARD_DATA);

  switch (tmp) {
  case -111:
    KeysPressed.W = false;
    break;
  case -98:
    KeysPressed.A = false;
    break;
  case -97:
    KeysPressed.S = false;
    break;
  case -96:
    KeysPressed.D = false;
    break;
  case -107:
    KeysPressed.Y = false;
    break;
  case -79:
    KeysPressed.N = false;
    break;
  }

  if (tmp <= 0)
    return;

  last_pressed = alphabet[tmp];
  char *s = " ";
  s[0] = last_pressed;

  switch (last_pressed) {
  case 'w':
    KeysPressed.W = true;
    break;
  case 'a':
    KeysPressed.A = true;
    break;
  case 's':
    KeysPressed.S = true;
    break;
  case 'd':
    KeysPressed.D = true;
    break;
  case 'y':
    KeysPressed.Y = true;
    break;
  case 'n':
    KeysPressed.N = true;
    break;
  }

  printf("%s", s);
}

void init_keyboard() {
  last_pressed = '\0';
  memset(&KeysPressed, 0, sizeof(KeysPressed));
  irq_install_handler(1, &on_irq1);
}