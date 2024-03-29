#include "../headers/screen.h"
#include "../headers/low_level.h"
#include "../headers/util.h"

extern char *alphabet;
extern char last_pressed;

void printf(char *str, ...) {
  // prints formatted string
  // %d - integer
  // %s - null-terminated string
  // %% - percent sign
  // %x - hex value

  void *beg = &str;
  int i;
  char *s = " ";
  char *tmp = "                    ";

  beg += sizeof(char *);
  for (i = 0; i < strlen(str); i++) {
    if (str[i] == '%') {
      switch (str[i + 1]) {
      case 's':
        print(*((char **)beg));
        beg += sizeof(char *);
        break;
      case 'd':
        itos(tmp, *((int *)beg));
        print(tmp);
        beg += sizeof(int);
        break;
      case '%':
        print("%");
        break;
      case 'x':
        itoh(tmp, *((int *)beg));
        print("0x");
        print(tmp);
        beg += sizeof(int);
        break;
      }
      i++;
    } else {
      s[0] = str[i];
      print(s);
    }
  }
}

uint32 getns(char *buf, uint32 n) {
  // gets first n or less byte from an user and adds '\0' at n+1 place
  // returns a length of the buf(without '\0')
  uint32 i = 0;
  uint32 started = get_cursor(); // it's doubled

  do {
    while (started - get_cursor() < 2) {
      __asm__("hlt");
    }
    if (last_pressed == '\b' && i > 0) {
      started -= 2;
      buf[--i] = '\0';
      continue;
    }
    started = get_cursor();
    buf[i++] = last_pressed;
  } while (last_pressed != '\n' && i < n);

  buf[i] = '\0';
  return i;
}

char getchar() {
  char *s = " ";
  getns(s, 1);
  return s[0];
}

uint32 gets(char *buf) {
  // gets a string from an user and saves it in the buf
  // returns a length of the buf(without '\0')
  int i = 0;
  uint32 started = get_cursor(); // it's doubled

  do {
    while (started - get_cursor() < 2) {
      __asm__("hlt");
    }
    if (last_pressed == '\b' && i > 0) {
      started -= 2;
      buf[--i] = '\0';
      continue;
    }
    started = get_cursor();
    buf[i++] = last_pressed;
  } while (last_pressed != '\n');

  buf[--i] = '\0';
  return i;
}

void clear_screen() {
  // clears screen by printing ' '(spaces) all over a screen
  // and sets a cursor at the begining
  set_cursor(get_screen_offset(0, ROWS - 1));
	for (int i = 0; i < ROWS; i++) {
		printf("\n");
  }
  set_cursor(0);
}

void print(char *str) {
  // prints a str and moves a cursor
  for (int i = 0; str[i] != '\0'; i++) {
    int offset = get_cursor() / 2;
    int row = offset / COLUMNS;
    int col = offset % COLUMNS;
    print_char(str[i], row, col, DEFAULT_COLOR_ATTR);
  }
}

void print_at_begin(char *str) {
  // prints at the begining of a screen
  print_at(str, 0, 0);
}

void print_at(char *str, int row, int col) {
  // prints on given row and column if row and col are in bounderies(>=0 and
  // <number of rows or columns) else prints at the begining
  if (row >= 0 && row < ROWS && col >= 0 && col < COLUMNS)
    set_cursor(get_screen_offset(col, row));
  else {
    set_cursor(0);
    row = 0;
    col = 0;
  }
  for (int i = 0; str[i] != '\0'; i++) {
    print_char(str[i], row, col, DEFAULT_COLOR_ATTR);
    int offset = get_cursor() / 2;
    row = offset / COLUMNS;
    col = offset % COLUMNS;
  }
}

void print_char(char c, int row, int col, char attr) {
  // prints one char on given row and column with given color attribute if row
  // and col are in bounderies if attr is not set(set to zero) default attribute
  // is used(white text on black background) if row and col aren't in bounderies
  // then current cursor position is used on newline('\n') the function moves
  // the cursor at the begining of the next line
  char *video_mem = (char *)VIDEO_MEMORY;

  if (!attr)
    attr = WHITE_ON_BLACK;

  int offset;
  if (row >= 0 && row < ROWS && col >= 0 && col < COLUMNS)
    offset = get_screen_offset(col, row);
  else
    offset = get_cursor();

  if (c == '\n') {
    int rows = offset / (2 * COLUMNS);
    offset = get_screen_offset(COLUMNS - 1, rows);
  } else if (c == '\b') {
    offset -= 4;
    set_cursor(offset);
    video_mem[offset + 2] = ' ';
    video_mem[offset + 3] = attr;
  } else {
    video_mem[offset] = c;
    video_mem[offset + 1] = attr;
  }

  offset += 2;
  offset = handle_scroll(offset);
  set_cursor(offset);
}

int get_screen_offset(int col, int row) {
  // returns screen offset
  // the value is doubled because for every position on a screen there're tow
  // bytes: first for char; second for attribute
  return (row * COLUMNS + col) * 2;
}

int get_cursor() {
  // returns current cursor offset
  write_byte(REG_SCREEN_CTRL, 14);
  int res = read_byte(REG_SCREEN_DATA) << 8;
  write_byte(REG_SCREEN_CTRL, 15);
  res += read_byte(REG_SCREEN_DATA);
  return res * 2;
}

int handle_scroll(int offset) {
  // handles scrolling if needed and returns new offset
  if (offset < ROWS * COLUMNS * 2)
    return offset;

  for (int i = 1; i < ROWS; i++) {
    memcopy((char *)(get_screen_offset(0, i) + VIDEO_MEMORY),
            (char *)(get_screen_offset(0, i - 1) + VIDEO_MEMORY), COLUMNS * 2);
  }
  char *last_row = (char *)(get_screen_offset(0, ROWS - 1) + VIDEO_MEMORY);
  for (int i = 0; i < COLUMNS * 2; i++)
    last_row[i] = 0;

  offset -= COLUMNS * 2;
  return offset;
}

void set_cursor(int offset) {
  // sets cursor by the offset
  offset /= 2;
  write_byte(REG_SCREEN_CTRL, 14);
  write_byte(REG_SCREEN_DATA, offset >> 8);
  write_byte(REG_SCREEN_CTRL, 15);
  write_byte(REG_SCREEN_DATA, offset);
}
