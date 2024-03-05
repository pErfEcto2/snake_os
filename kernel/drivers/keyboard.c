#include "../headers/keyboard.h"
#include "../headers/low_level.h"
#include "../headers/screen.h"
#include "../idt/idt.h"

volatile char last_pressed;
char *alphabet = "001234567890-=\b0qwertyuiop[]\n\\asdfghjkl;'000zxcvbnm,./"
                 "000 0000000000000000000000000000000000000000000000000000";

void on_irq1(struct InterruptRegisters *regs) {
  char tmp = read_byte(REG_KEYBOARD_DATA);
  if (tmp <= 0)
    return;

  last_pressed = alphabet[tmp];
  char *s = " ";
  s[0] = last_pressed;
  printf("%s", s);
}

void init_keyboard() {
  last_pressed = '\0';
  irq_install_handler(1, &on_irq1);
}