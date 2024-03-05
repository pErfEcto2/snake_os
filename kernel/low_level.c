unsigned char read_byte(unsigned short port) {
  // reads a byte from the port
  unsigned char res;
  __asm__("in %%dx, %%al" : "=a"(res) : "d"(port));
  return res;
}

void write_byte(unsigned short port, unsigned char data) {
  // writes a byte to the port
  __asm__("out %%al, %%dx" : : "a"(data), "d"(port));
}

unsigned short read_word(unsigned short port) {
  // reads a word(two bytes) from the port
  unsigned short res;
  __asm__("in %%dx, %%ax" : "=a"(res) : "d"(port));
  return res;
}

void write_word(unsigned short port, unsigned short data) {
  // writes a word(tow bytes) to the port
  __asm__("out %%ax, %%dx" : : "a"(data), "d"(port));
}
