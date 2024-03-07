#include "headers/util.h"
#include "headers/low_level.h"
#include "headers/screen.h"
#include "stdint.h"


static uint32 next = 1;
void srand(int n) {
	// seeds pseudorandom number generator
	// if n is zero noise from io port is used
	if (n == 0) next = read_word(64);
	else next = n;
}

uint32 rand() {
	// generats pseudorandom numbers
	next = next * 1103515245 + 12345;
  return (uint32)(next / 65536) % RAND_MAX;
}

void wait_until_key_pressed() {
  // waits until an user presses any key
  uint32 started = get_cursor();
  while (get_cursor() - started <= 0) {
    __asm__("hlt");
  }
  set_cursor(started);
  print_at("", started / 2 / COLUMNS, (started / 2) % COLUMNS);
}

void memset(void *buf, char val, uint32 n) {
  // sets first n bytes of the buf to val
  char *tmp = (char *)buf;
  for (; n > 0; n--)
    *tmp++ = val;
}

void print_all_info() {
  // prints contents of all registers
  register int eax asm("eax"), ebx asm("ebx"), ecx asm("ecx"), edx asm("edx"),
      esp asm("esp"), ebp asm("ebp"), edi asm("edi"), esi asm("esi");

  printf("eax=%d ebx=%d ecx=%d edx=%d esp=%d ebp=%d edi=%d esi=%d\n", eax, ebx,
         ecx, edx, esp, ebp, edi, esi);
}

int htoi(char *hex) {
  // converts hex to int and returns it
  // the hex must be without any prefixes
  // on error returns -1
  uint32 val = 0;
  while (*hex) {
    uint8 byte = *hex++;
    if (byte >= '0' && byte <= '9')
      byte = byte - '0';
    else if (byte >= 'a' && byte <= 'f')
      byte = byte - 'a' + 10;
    else if (byte >= 'A' && byte <= 'F')
      byte = byte - 'A' + 10;
    else
      return -1;
    val = (val << 4) | (byte & 0xF);
  }
  return val;
}

void itoh(char *str, int val) {
  // converts int val to hex and stores it in the str
  int i = 0, temp;
  while (val != 0) {
    temp = val % 16;
    if (temp < 10)
      temp = temp + '0';
    else
      temp = temp + 'a' - 10;
    str[i++] = temp;
    val = val / 16;
  }
  srev(str, i);
  str[i + 1] = '\0';
}

int strlen(char *str) {
  // returns a length of a str
  int res = 0;

  while (*str++)
    res++;
  return res;
}

void memcopy(char *src, char *dest, int n) {
  // copies n byte from src to dest
  for (int i = 0; i < n; i++)
    *(dest + i) = *(src + i);
}

void srev(char *str, unsigned int n) {
  // reverses str
  unsigned int start = 0;
  unsigned int end = n - 1;
  char tmp;
  while (start < end) {
    tmp = str[start];
    str[start] = str[end];
    str[end] = tmp;
    start++;
    end--;
  }
}

void itos(char *str, int val) {
  // converts int to string
  // the size of the str must be large enough to store all digits of the int
  int is_negative = 0;

  if (val < 0) {
    is_negative = 1;
    val = -val;
  }

  int i = 0;
  while (val != 0) {
    str[i++] = '0' + (val % 10);
    val = val / 10;
  }

  if (is_negative) {
    str[i++] = '-';
  }

  if (i == 0) {
    str[i++] = '0';
  }

  str[i] = '\0';

  srev(str, i);
}

int stoi(char *str) {
  // converts str to int
  // if invalid string is given, returns -1
  int res = 0;
  short sign = 1;

  for (int i = 0; *str; i++) {
    if (((*str < '0' || *str > '9') && *str != '-') || (*str == '-' && i != 0)) {
      return -1;
    }

    if (i == 0 && *str == '-') {
      sign = -1;
      str++;
      continue;
    }

    res = res * 10 + *str - '0';
    str++;
  }
  return sign * res;
}

extern volatile uint64 ticks;
void sleep(unsigned int millis) {
  // waits millis milliseconds
  // magic value to adjust inner speed(ticks per second) with the actual time
  uint32 last_tick = millis * 22 + ticks;
  while (ticks < last_tick) {
    __asm__("hlt");
  }
}
