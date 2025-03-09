#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t volume) {
  int result = 0;

  for (s21_size_t i = 0; i < volume; i++) {
    if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0') {
      result = (unsigned char)str1[i] - (unsigned char)str2[i];
      volume = i;
    }
  }

  return result;
}
