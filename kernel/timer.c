#include "headers/timer.h"
#include "headers/low_level.h"
#include "headers/screen.h"
#include "idt/idt.h"

volatile uint64 ticks;
void on_irq0(struct InterruptRegisters *regs) { ticks++; }

void init_timer() {
  ticks = 0;
  irq_install_handler(0, &on_irq0);

  uint32 div = 55; // max frequency(as far as i know)

  write_byte(REG_TIMER_CMD, 0x36);
  write_byte(REG_TIMER_DATA1, div & 0xff);
  write_byte(REG_TIMER_DATA1, (div >> 8) & 0xff);
}
