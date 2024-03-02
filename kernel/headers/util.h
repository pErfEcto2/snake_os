#define REG_KEYBOARD_DATA 0x60


void memcopy(char *src, char *dest, int n);
void sleep(unsigned int millis);

int stoi(char *str);
void itos(char *str, int val);
float stof(char *str);
void ftos(char *str, float val);

void srev(char *str, unsigned int n);
int strlen(char *str);

int gets(char *buf);
void getns(char *buf, unsigned int n);

void printf(char *str, ...);
