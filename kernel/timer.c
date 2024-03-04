#include "headers/timer.h"
#include "headers/low_level.h"
#include "headers/screen.h"
#include "headers/util.h"

volatile uint32 ticks;

void on_irq0(struct InterruptRegisters *regs) {
  __asm__("cli");
  printf("%d\n", ticks);
  ticks++;
}

void init_timer() {
  ticks = 0;
  irq_install_handler(0, &on_irq0);

  uint32 div = 1193182 / 10;

  write_byte(REG_TIMER_CMD, 0x36);
  write_byte(REG_TIMER_DATA1, div & 0xff);
  write_byte(REG_TIMER_DATA1, (div >> 8) & 0xff);
  return;
}

uint32 read_pit_count() {
  uint32 res = 0;

  __asm__("cli");
  write_byte(REG_TIMER_CMD, 0x0);

  res = read_byte(REG_TIMER_DATA1);
  res |= read_byte(REG_TIMER_DATA1) << 8;
  return res;
}
