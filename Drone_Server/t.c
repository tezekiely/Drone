#include <stdlib.h>
#include <stdio.h>
int main() {
  char *sentence = "Rudolph years old";
  char str[20];
  char *a = malloc(256);
  char b[10];
  sscanf(sentence, "%s %s %s", str, a, b);
  printf("%s\n", str);
  printf("%s\n", a);
  printf("%s\n", b);
  return 0;
}