#include "../idt/idt.h"

#define REG_TIMER_CMD 0x43
#define REG_TIMER_DATA1 0x40

void init_timer();
uint32 read_pit_count();

