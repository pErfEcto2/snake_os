#include "headers/util.h"
#include "stdint.h"


void memset(void *buf, char val, uint32 n) {
	// sets every n bytes of the buf to val
	char *tmp = (char*)buf;
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

float stof(char *str) {
  // converts from str to float and returns it
  // if invalid str is given the function returns -1

  return -1.0;
}

void ftos(char *str, float val) {
  // converts float to str
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
    if ((*str < '0' || *str > '9') && *str != '-' || (*str == '-' && i != 0)) {
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

void sleep(unsigned int millis) {}
