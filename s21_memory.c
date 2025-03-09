#include <stddef.h>
#include <stdio.h>

#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *p = str;
  while (n-- > 0) {
    if (*p == (unsigned char)c) return (void *)p;
    p++;
  }
  return S21_NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *p1 = str1;
  const unsigned char *p2 = str2;
  s21_size_t counter = n;
  while (counter-- && *p1 && *p2 && *p1 == *p2) {
    ++p1;
    ++p2;
  }
  int result = 0;
#if defined(__linux__)
  if (*p1 < *p2 && n != 0) {
    result = -1;
  } else if (*p1 > *p2 && n != 0) {
    result = 1;
  }
#endif

#if defined(__APPLE__)
  result = n != 0 ? (int)(*p1 - *p2) : 0;
#endif
  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *d = dest;
  const unsigned char *s = src;

  for (s21_size_t i = 0; i < n; ++i) {
    d[i] = s[i];
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *p = str;
  for (s21_size_t i = 0; i < n; ++i) {
    p[i] = (unsigned char)c;
  }
  return str;
}

s21_size_t s21_strlen(const char *str) {
  const char *p = str;
  while (*p++) {
  }
  return (s21_size_t)(p - str - 1);
}
