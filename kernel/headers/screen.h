#define VIDEO_MEMORY 0xb8000
#define ROWS 25
#define COLUMNS 80
#define WHITE_ON_BLACK 0x0f
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void clear_screen();
void print_at_begin(char *str);
void print_at(char *str, int row, int col);
void print_char(char c, int row, int col, char attr);
int get_screen_offset(int col, int row);
int get_cursor();
int handle_scroll(int offset);
void set_cursor(int offset);

