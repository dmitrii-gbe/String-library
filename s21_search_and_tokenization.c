#include <stddef.h>

#include "s21_string.h"

int is_delimiter(char c, const char *delim) {
  int found = 0;
  while (*delim && !found) {
    if (c == *delim) {
      found = 1;
    }
    delim++;
  }
  return found;
}

char *s21_strchr(const char *str, int c) {
  char *result = S21_NULL;
  int found = 0;
  while (*str && !found) {
    if (*str == (char)c) {
      result = (char *)str;
      found = 1;
    }
    str++;
  }
  return result;
}

char *s21_strrchr(const char *str, int c) {
  const char *last_occurrence = S21_NULL;
  while (*str) {
    if (*str == (char)c) {
      last_occurrence = str;
    }
    str++;
  }
  return (char *)last_occurrence;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;
  if (!*needle) {
    return (char *)haystack;
  }
  int found = 0;
  for (; *haystack && !found; haystack++) {
    const char *h = haystack;
    const char *n = needle;
    while (*h && *n && (*h == *n)) {
      h++;
      n++;
    }
    if (!*n) {
      result = (char *)haystack;
      found = 1;
    }
  }
  return result;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  int found_out = 0;
  while (*str1 && !found_out) {
    const char *s2 = str2;
    int found_in = 0;
    while (*s2 && !found_in) {
      if (*str1 == *s2) {
        result = (char *)str1;
        found_in = 1;
      }
      s2++;
    }
    if (result) {
      found_out = 1;
    }
    str1++;
  }
  return result;
}

char *s21_strtok(char *str, const char *delim) {
  static char *last = S21_NULL;
  char *result = S21_NULL;

  if (str == S21_NULL) {
    str = last;
  }
  while (*str && is_delimiter(*str, delim)) {
    str++;
  }
  if (*str) {
    result = str;
    while (*str && !is_delimiter(*str, delim)) {
      str++;
    }
    if (*str) {
      *str++ = '\0';
    }
    last = str;
  }
  return result;
}
