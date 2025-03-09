#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  int count = 0;
  while (dest[count] != '\0') {
    count++;
  }
  s21_size_t j = 0;
  while (j < n && src[j] != '\0') {
    dest[count++] = src[j++];
  }
  dest[count] = '\0';
  return dest;
}
