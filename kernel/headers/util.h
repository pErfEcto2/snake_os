#pragma once

#define RAND_MAX 32768

#define REG_KEYBOARD_DATA 0x60
#include "../stdint.h"

void print_all_info();

void memcopy(char *src, char *dest, int n);
void memset(void *buf, char val, uint32 n);

void sleep(unsigned int millis);
void wait_until_key_pressed();

int stoi(char *str);
void itos(char *str, int val);
int htoi(char *hex);
void itoh(char *str, int val);

void srev(char *str, unsigned int n);
int strlen(char *str);

void srand(int n);
int rand();
