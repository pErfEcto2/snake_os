#include "headers/keyboard.h"
#include "headers/screen.h"
#include "headers/util.h"

#define WIDTH COLUMNS - 2
#define HEIGHT ROWS - 2

typedef struct Vec2 {
  uint32 x;
  uint32 y;
} Vec2;

typedef enum { UP, DOWN, LEFT, RIGHT } Direction;
extern struct KeysPressed KeysPressed;
char stop;

void print_top(uint32 score);
void print_apple(Vec2 apple);
void print_snake(Vec2 head, Direction *dirs, uint32 len);
void print_bounderies();

void main() {
  clear_screen();
  srand(0);

  printf("hi, do u wanna play the snake game?\nActually, u have no choice\n"
         "Controls on wasd\nPress any key to start\n");
  wait_until_key_pressed();
  clear_screen();

  uint32 record = 0;
  Vec2 head, apple;
  Direction dirs[WIDTH * HEIGHT];
  uint32 len;
  uint32 score;
  Direction dir;

start:
  clear_screen();
  print_bounderies();

  head.x = 10;
  head.y = 10;

  apple.x = 2 + (rand() % (WIDTH - 1));
  apple.y = 2 + (rand() % (HEIGHT - 1));

  len = 1;
  stop = false;
  score = 1;
  dir = RIGHT;

  while (!stop) {
    if (KeysPressed.W && dir != DOWN)
      dir = UP;
    else if (KeysPressed.A && dir != RIGHT)
      dir = LEFT;
    else if (KeysPressed.S && dir != UP)
      dir = DOWN;
    else if (KeysPressed.D && dir != LEFT)
      dir = RIGHT;

    switch (dir) {
    case UP:
      head.y--;
      break;
    case DOWN:
      head.y++;
      break;
    case LEFT:
      head.x--;
      break;
    case RIGHT:
      head.x++;
      break;
    }

    if (head.x < 1 || head.x > WIDTH || head.y < 1 || head.y > HEIGHT) {
      stop = true;
      break;
    }

    uint32 adjust = (head.x == apple.x && head.y == apple.y);
    for (int i = len - 1 + adjust; i >= 0; i--) {
      dirs[i + 1] = dirs[i];
    }
    dirs[0] = dir;
    if (adjust) {
      score++;
      len++;
      apple.x = 2 + (rand() % (WIDTH - 1));
      apple.y = 2 + (rand() % (HEIGHT - 1));
    }

    print_top(score);
    print_snake(head, dirs, len);
    print_apple(apple);
    set_cursor(0);

    sleep(100);
  }
  clear_screen();

  if (score > record) {
    record = score;
    printf("Congrats! You set new record: %d\n", record);
  } else {
    printf("Almost did it! Your score is %d; the record is %d\n", score,
           record);
  }

  sleep(700);
  printf("Press any key to restart");
  wait_until_key_pressed();
  goto start;
}

void print_bounderies() {
  set_cursor(0);
  for (int i = 1; i < COLUMNS - 1; i++)
    print_at("#", 0, i);

  for (int i = 1; i < ROWS - 1; i++)
    print_at("#", i, 0);

  for (int i = 1; i < ROWS - 1; i++)
    print_at("#", i, COLUMNS - 1);

  for (int i = 1; i < COLUMNS - 1; i++)
    print_at("#", ROWS - 1, i);
}

void print_top(uint32 score) {
  set_cursor(get_screen_offset(COLUMNS / 2 - 8, 0));
  printf("  Score: %d   ", score);
}

void print_apple(Vec2 apple) {
  set_cursor(get_screen_offset(apple.x, apple.y));
  printf("@");
}

void print_snake(Vec2 head, Direction *dirs, uint32 len) {
  set_cursor(get_screen_offset(head.x, head.y));
  printf("o");

  Vec2 tmp = head;
  for (uint32 i = 0; i < len; i++) {
    switch (dirs[i]) {
    case UP:
      tmp.y++;
      break;
    case DOWN:
      tmp.y--;
      break;
    case LEFT:
      tmp.x++;
      break;
    case RIGHT:
      tmp.x--;
      break;
    }

    if (head.x == tmp.x && head.y == tmp.y)
      stop = true;
  }
  set_cursor(get_screen_offset(tmp.x, tmp.y));
  printf(" ");
}
