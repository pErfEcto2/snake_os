#include "idt.h"
#include "../headers/low_level.h"
#include "../headers/screen.h"
#include "../headers/util.h"
#include "../stdint.h"

struct idt_entry_struct idt_entries[256];
struct idt_ptr_struct idt_ptr;

extern void idt_flush(uint32);

void init_idt() {
  idt_ptr.limit = sizeof(struct idt_entry_struct) * 256 - 1;
  idt_ptr.base = (uint32)&idt_entries;

  memset(&idt_entries, 0, sizeof(struct idt_entry_struct) * 256);

  write_byte(PIC_CMD1, 0x11);
  write_byte(PIC_CMD2, 0x11);

  write_byte(PIC_DATA1, 0x20);
  write_byte(PIC_DATA2, 0x28);

  write_byte(PIC_DATA1, 0x04);
  write_byte(PIC_DATA2, 0x02);

  write_byte(PIC_DATA1, 0x01);
  write_byte(PIC_DATA2, 0x01);

  write_byte(PIC_DATA1, 0x0);
  write_byte(PIC_DATA2, 0x0);

  setIdtGate(0, (uint32)isr0, 0x08, 0x8E);
  setIdtGate(1, (uint32)isr1, 0x08, 0x8E);
  setIdtGate(2, (uint32)isr2, 0x08, 0x8E);
  setIdtGate(3, (uint32)isr3, 0x08, 0x8E);
  setIdtGate(4, (uint32)isr4, 0x08, 0x8E);
  setIdtGate(5, (uint32)isr5, 0x08, 0x8E);
  setIdtGate(6, (uint32)isr6, 0x08, 0x8E);
  setIdtGate(7, (uint32)isr7, 0x08, 0x8E);
  setIdtGate(8, (uint32)isr8, 0x08, 0x8E);
  setIdtGate(9, (uint32)isr9, 0x08, 0x8E);
  setIdtGate(10, (uint32)isr10, 0x08, 0x8E);
  setIdtGate(11, (uint32)isr11, 0x08, 0x8E);
  setIdtGate(12, (uint32)isr12, 0x08, 0x8E);
  setIdtGate(13, (uint32)isr13, 0x08, 0x8E);
  setIdtGate(14, (uint32)isr14, 0x08, 0x8E);
  setIdtGate(15, (uint32)isr15, 0x08, 0x8E);
  setIdtGate(16, (uint32)isr16, 0x08, 0x8E);
  setIdtGate(17, (uint32)isr17, 0x08, 0x8E);
  setIdtGate(18, (uint32)isr18, 0x08, 0x8E);
  setIdtGate(19, (uint32)isr19, 0x08, 0x8E);
  setIdtGate(20, (uint32)isr20, 0x08, 0x8E);
  setIdtGate(21, (uint32)isr21, 0x08, 0x8E);
  setIdtGate(22, (uint32)isr22, 0x08, 0x8E);
  setIdtGate(23, (uint32)isr23, 0x08, 0x8E);
  setIdtGate(24, (uint32)isr24, 0x08, 0x8E);
  setIdtGate(25, (uint32)isr25, 0x08, 0x8E);
  setIdtGate(26, (uint32)isr26, 0x08, 0x8E);
  setIdtGate(27, (uint32)isr27, 0x08, 0x8E);
  setIdtGate(28, (uint32)isr28, 0x08, 0x8E);
  setIdtGate(29, (uint32)isr29, 0x08, 0x8E);
  setIdtGate(30, (uint32)isr30, 0x08, 0x8E);
  setIdtGate(31, (uint32)isr31, 0x08, 0x8E);

  setIdtGate(32, (uint32)irq0, 0x08, 0x8E);
  setIdtGate(33, (uint32)irq1, 0x08, 0x8E);
  setIdtGate(34, (uint32)irq2, 0x08, 0x8E);
  setIdtGate(35, (uint32)irq3, 0x08, 0x8E);
  setIdtGate(36, (uint32)irq4, 0x08, 0x8E);
  setIdtGate(37, (uint32)irq5, 0x08, 0x8E);
  setIdtGate(38, (uint32)irq6, 0x08, 0x8E);
  setIdtGate(39, (uint32)irq7, 0x08, 0x8E);
  setIdtGate(40, (uint32)irq8, 0x08, 0x8E);
  setIdtGate(41, (uint32)irq9, 0x08, 0x8E);
  setIdtGate(42, (uint32)irq10, 0x08, 0x8E);
  setIdtGate(43, (uint32)irq11, 0x08, 0x8E);
  setIdtGate(44, (uint32)irq12, 0x08, 0x8E);
  setIdtGate(45, (uint32)irq13, 0x08, 0x8E);
  setIdtGate(46, (uint32)irq14, 0x08, 0x8E);
  setIdtGate(47, (uint32)irq15, 0x08, 0x8E);

  setIdtGate(128, (uint32)isr128, 0x08, 0x8E); // System calls
  setIdtGate(177, (uint32)isr177, 0x08, 0x8E); // System calls

  idt_flush((uint32)&idt_ptr);
}

void setIdtGate(uint8 num, uint32 base, uint16 sel, uint8 flags) {

  idt_entries[num].base_low = base & 0xFFFF;
  idt_entries[num].base_high = (base >> 16) & 0xFFFF;
  idt_entries[num].sel = sel;
  idt_entries[num].always0 = 0;
  idt_entries[num].flags = flags | 0x60;
}

char *exception_messages[] = {"Division By Zero",
                              "Debug",
                              "Non Maskable Interrupt",
                              "Breakpoint",
                              "Into Detected Overflow",
                              "Out of Bounds",
                              "Invalid Opcode",
                              "No Coprocessor",
                              "Double fault",
                              "Coprocessor Segment Overrun",
                              "Bad TSS",
                              "Segment not present",
                              "Stack fault",
                              "General protection fault",
                              "Page fault",
                              "Unknown Interrupt",
                              "Coprocessor Fault",
                              "Alignment Fault",
                              "Machine Check",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved",
                              "Reserved"};

void isr_handler(struct InterruptRegisters *regs) {
  if (regs->int_no < 32) {
    printf("Kernel panic: %s\n", exception_messages[regs->int_no]);
    print_all_info();
    __asm__("cli; hlt");
  }
}

void *irq_routines[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void irq_install_handler(int irq,
                         void (*handler)(struct InterruptRegisters *r)) {
  irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq) { irq_routines[irq] = 0; }

void irq_handler(struct InterruptRegisters *regs) {
  void (*handler)(struct InterruptRegisters *regs);

  handler = irq_routines[regs->int_no - 32];

  if (handler) {
    handler(regs);
  }

  if (regs->int_no >= 40) {
    write_byte(PIC_CMD2, 0x20);
  }

  write_byte(PIC_CMD1, 0x20);
}
