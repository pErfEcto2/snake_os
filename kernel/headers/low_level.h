#define WHITE_ON_BLACK 0x0f // white fr; black bg

unsigned char read_byte(unsigned short port);
void write_byte(unsigned short port, unsigned char data);
unsigned short read_word(unsigned short port);
void write_word(unsigned short port, unsigned short data);
