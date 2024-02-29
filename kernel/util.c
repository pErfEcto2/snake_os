void memcopy(char *src, char *dest, int n) {
  for (int i = 0; i < n; i++)
    *(dest + i) = *(src + i);
}