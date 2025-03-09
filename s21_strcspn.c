#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int len2 = s21_strlen(str2);
  int count = 0;
  const char *s = str1;

  while (*s != '\0') {
    int i;
    for (i = 0; i < len2; i++) {
      if (*s == str2[i]) {
        return count;
      }
    }
    s++;
    count++;
  }

  return count;
}
