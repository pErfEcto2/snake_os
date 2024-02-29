#include "../headers/screen.h"
#include "../headers/low_level.h"
#include "../headers/util.h"

void clear_screen() {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++)
      print_at(" ", i, j);
  }
  set_cursor(0);
}

void print(char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    int offset = get_cursor() / 2;
    int row = offset / COLUMNS;
    int col = offset % COLUMNS;
    print_char(str[i], row, col, DEFAULT_COLOR_ATTR);
  }
}

void print_at_begin(char *str) { print_at(str, 0, 0); }

void print_at(char *str, int row, int col) {
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
  } else {
    video_mem[offset] = c;
    video_mem[offset + 1] = attr;
  }

  offset += 2;
  offset = handle_scroll(offset);
  set_cursor(offset);
}

int get_screen_offset(int col, int row) { return (row * COLUMNS + col) * 2; }

int get_cursor() {
  write_byte(REG_SCREEN_CTRL, 14);
  int res = read_byte(REG_SCREEN_DATA) << 8;
  write_byte(REG_SCREEN_CTRL, 15);
  res += read_byte(REG_SCREEN_DATA);
  return res * 2;
}

int handle_scroll(int offset) {
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
  offset /= 2;
  write_byte(REG_SCREEN_CTRL, 14);
  write_byte(REG_SCREEN_DATA, offset >> 8);
  write_byte(REG_SCREEN_CTRL, 15);
  write_byte(REG_SCREEN_DATA, offset);
}
