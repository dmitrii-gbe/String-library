#include <ctype.h>

#include "s21_string.h"

int s21_Log(long num, const int base) {
  int result = 0;
  while (num >= base) {
    num /= base;
    ++result;
  }
  return result;
}

long double s21_Pow(const int base, int degree) {
  long double result = 1;
  int negative_degree = degree < 0;
  degree = negative_degree ? degree * (-1) : degree;
  long double tmp = base;
  while (degree > 0) {
    if (degree % 2 == 0) {
      tmp *= tmp;
      degree /= 2;
    } else {
      result *= tmp;
      --degree;
    }
  }
  return negative_degree ? 1.0L / result : result;
}

long double s21_Fabsl(long double val) { return (val < 0) ? -1.0 * val : val; }

void s21_strcpy(const char *from, char *to) {
  while ((*to++ = *from++)) {
  }
}

void s21_strcpyn(const char *from, char *to, int *const max_char,
                 const int wchar) {
  if (wchar) {
    wchar_t *act = (wchar_t *)to;
    while (*max_char > 0 && (*act++ = *from++)) {
      --(*max_char);
    }
  } else {
    while (*max_char > 0 && (*to++ = *from++)) {
      --(*max_char);
    }
  }
}

void s21_strcpynws(const char *from, char *to, int *const max_char,
                   int *const preceeding_ws, const int wchar) {
  while (isspace(*from)) {
    ++from;
    ++(*preceeding_ws);
  }
  if (wchar) {
    wchar_t *act = (wchar_t *)to;
    while (!isspace(*from) && *max_char > 0 && (*act++ = *from++)) {
      --(*max_char);
    }
    *act = L'\0';
  } else {
    while (!isspace(*from) && *max_char > 0 && (*to++ = *from++)) {
      --(*max_char);
    }
    *to = 0;
  }
}

void s21_ToUpperInternal(char *const str) {
  s21_size_t len = s21_strlen(str);
  for (s21_size_t i = 0; i < len; ++i) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      str[i] -= 32;
    }
  }
}

void s21_ToLowerInternal(char *const str) {
  s21_size_t len = s21_strlen(str);
  for (s21_size_t i = 0; i < len; ++i) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      str[i] += 32;
    }
  }
}

void *s21_to_upper(const char *str) {
  char *new = S21_NULL;
  if (str) {
    new = calloc(sizeof(char), s21_strlen(str) + 1);
    if (new != S21_NULL) {
      s21_strcpy(str, new);
      s21_ToUpperInternal(new);
    }
  }
  return new;
}

void *s21_to_lower(const char *str) {
  char *new = S21_NULL;
  if (str) {
    new = calloc(sizeof(char), s21_strlen(str) + 1);
    if (new != S21_NULL) {
      s21_strcpy(str, new);
      s21_ToLowerInternal(new);
    }
  }
  return new;
}

int s21_GetRadix(const char *str) {
  int radix = 0;
  while (isspace(*str)) {
    ++str;
  }
  if (*str == '-') {
    ++str;
  }
  if (*str == '0') {
    if (*(str + 1) == 'x' || *(str + 1) == 'X') {
      radix = 16;
    } else {
      radix = 8;
    }
  } else {
    radix = 10;
  }
  return radix;
}

void s21_AssignProceedVariable(const char c, const int base,
                               int *const proceed) {
  if (base == 8) {
    *proceed = c >= '0' && c <= '7';
  } else if (base == 10) {
    *proceed = s21_IsDigit(c);
  } else if (base == 16) {
    *proceed = s21_IsDigit(c) || s21_IsExtraHexadecimalDigit(c);
  }
}

void s21_AssignToSubtractVariable(const char c, int base,
                                  int *const to_subtract) {
  if (base <= 10) {
    *to_subtract = '0';
  } else if (base == 16) {
    if (s21_IsDigit(c)) {
      *to_subtract = '0';
    } else if (s21_IsExtraHexadecimalDigit(c)) {
      *to_subtract = 55;
    }
  }
}

long long s21_atol(const char *const source, const int base, int *const shift,
                   int max_char, int *const success) {
  /* printf("Atol source: %s\n", source); */
  char *str = s21_to_upper(source);
  char *ptr_to_free = str;
  while (isspace(*str)) {
    ++str;
    ++(*shift);
  }
  int negative = 0;
  if (str[0] == '-') {
    negative = 1;
    --max_char;
    ++str;
    ++*shift;
  }
  if ((base == 16 && str[0] == '0' && (str[1] == 'X' || str[1] == 'x'))) {
    /* printf("IF\n"); */
    *shift += 2;
    str += 2;
  }

  long long result = 0;
  const s21_size_t len = s21_strlen(str);
  s21_size_t i = 0;
  int to_subtract = '0';
  int proceed = 0;
  s21_AssignProceedVariable(str[i], base, &proceed);
  for (; i < len && proceed && max_char > 0;) {
    result *= base;
    s21_AssignToSubtractVariable(str[i], base, &to_subtract);
    result += str[i] - to_subtract;
    *success = 1;
    ++i;
    --max_char;
    ++(*shift);
    s21_AssignProceedVariable(str[i], base, &proceed);
  }
  /* printf("Success: %d\n", *success); */
  free(ptr_to_free);
  return negative ? -1 * result : result;
}

long double s21_atold(const char *const source, const int parse_exponent,
                      int *const shift, int max_char) {
  const char *str = source;
  s21_size_t i = 0;
  while (isspace(*(str + i))) {
    ++i;
    ++(*shift);
  }
  long double result = 0;
  int negative = str[i] == '-' && s21_strlen(str + i) > 1;
  i += negative;
  max_char -= negative;
  int success = 0;
  int old_shift;
  result +=
      str[i] == '.' ? 0 : s21_atol(str + i, 10, shift, max_char, &success);
  success = str[i] == '.' || success;
  max_char -= s21_Log(result, 10) + 1;
  *shift += negative ? 1 : 0;
  while (s21_IsDigit(str[i])) {
    ++i;
  }
  if (str[i] == '.') {
    ++i;
    --max_char;
    ++(*shift);
    int tmp = 0;
    old_shift = *shift;
    long double mantissa =
        (long double)s21_atol(str + i, 10, shift, max_char, &tmp);
    *shift = tmp ? *shift : old_shift;
    int count = mantissa > 0 ? s21_Log(mantissa, 10) + 1 : 0;
    max_char -= count;
    result += mantissa / s21_Pow(10, count);
  }
  while (s21_IsDigit(str[i])) {
    ++i;
  }
  if ((str[i] == 'E' || str[i] == 'e') && parse_exponent) {
    --max_char;
    int tmp = 0;
    old_shift = *shift;
    int degree = s21_atol(str + i + 1, 10, shift, max_char, &tmp);

    result *= (long double)s21_Pow(10, degree);
    *shift = tmp ? *shift : old_shift;
    ++(*shift);
  }
  *shift = success ? *shift : 0;
  return negative ? (long double)(-1) * result : result;
}

int s21_IsDigit(const char c) { return c >= '0' && c <= '9'; }

int s21_IsExtraHexadecimalDigit(const char c) {
  return (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}

void s21_InitializeFormat(Format *const f) {
  f->width = INT_MAX;
  f->length = 0;
  f->value_type = 0;
  f->suppress_assignment = 0;
  f->accuracy = -1;
  for (int i = 0; i < '0' + 1; ++i) {
    f->flags[i] = 0;
  }
}

int s21_AnyOf(const char c, const char *str) {
  int found = 0;
  while (*str && !found) {
    found = c == *str++;
  }
  return found;
}

void AdjustFormat(Format *const f, const int sprintf) {
  if (sprintf) {
    char *integer_types = "diouxX";
    if (s21_AnyOf(f->value_type, "gG") && f->accuracy == 0) {
      f->accuracy = 1;
    }
    if (f->value_type == 'u') {
      f->flags['+'] = 0;
    }
    if (f->flags['+']) {
      f->flags[' '] = 0;
    }
    if (f->flags['-']) {
      f->flags['0'] = 0;
    }
    if (f->flags['0'] && s21_AnyOf(f->value_type, integer_types) &&
        f->accuracy != -1) {
      f->flags['0'] = 0;
    }
    f->accuracy = f->accuracy == -1 &&
                          !s21_AnyOf(f->value_type, integer_types) &&
                          f->value_type != 's' && f->value_type != 'c'
                      ? 6
                      : f->accuracy;
    if (f->value_type == 'p') {
      f->value_type = 'x';
      f->flags['#'] = 1;
      f->length = 'l';
    }
  } else {
    f->value_type = f->value_type > 96 ? f->value_type - 32 : f->value_type;
    f->value_type =
        (f->value_type == 'F' || f->value_type == 'G') ? 'E' : f->value_type;
    if (f->value_type == 'P') {
      f->value_type = 'X';
      f->length = 'l';
    } else if (f->value_type == 'C' && f->width == INT_MAX) {
      f->width = 1;
    }
  }
}

Format s21_ParseFormatSpecifier(const char *str, int *const format_len,
                                const int sprintf) {
  char *value_types = "cdieEfFgGosuxXpn%";
  char *length_modiers = "lLh";
  char *flags = "+-# 0";
  Format f;
  s21_InitializeFormat(&f);
  ++str;
  int len = s21_strlen(str);
  int i = 0;
  for (; i < len && !f.value_type;) {
    if (str[i] == '*') {
      f.suppress_assignment = sprintf ? f.suppress_assignment : 1;
      f.width = sprintf ? ASTERISK : f.width;
      ++i;
    } else if (s21_IsDigit(str[i]) && str[i] != '0') {
      int shift = 0, success = 0;
      f.width = s21_atol(str + i, 10, &shift, INT_MAX, &success);
      i += shift;
    } else if (s21_AnyOf(str[i], value_types)) {
      f.value_type = str[i];
      ++i;
    } else if (s21_AnyOf(str[i], length_modiers)) {
      f.length = str[i];
      ++i;
    } else if (s21_AnyOf(str[i], flags)) {
      f.flags[str[i] + 0] = 1;
      ++i;
    } else if (str[i] == '.') {
      ++i;
      if (s21_IsDigit(str[i])) {
        int shift = 0, success = 0;
        f.accuracy = s21_atol(str + i, 10, &shift, INT_MAX, &success);
        i += shift;
      } else if (str[i] == '*') {
        f.accuracy = ASTERISK;
        ++i;
      } else {
        f.accuracy = 0;
      }
    }
  }
  AdjustFormat(&f, sprintf);
  *format_len = i;
  return f;
}

void s21_ReadAndAssignInt(va_list *const arg_list, const Format *const format,
                          const char *str, int *const shift,
                          const int total_symbols) {
  long value = 0;
  int success = 0;
  if (format->value_type == 'I') {
    value = s21_atol(str, s21_GetRadix(str), shift, format->width, &success);
  } else if (format->value_type == 'D' || format->value_type == 'U') {
    value = s21_atol(str, 10, shift, format->width, &success);
  } else if (format->value_type == 'O') {
    value = s21_atol(str, 8, shift, format->width, &success);
  } else if (format->value_type == 'X') {
    value = s21_atol(str, 16, shift, format->width, &success);
  } else if (format->value_type == 'N') {
    value = total_symbols;
    success = 1;
  }
  if (!format->suppress_assignment && success) {
    if (format->length == 'l') {
      long *ptr = va_arg(*arg_list, long *);
      *ptr = value;
    } else if (format->length == 'h') {
      short *ptr = va_arg(*arg_list, short *);
      *ptr = value;
    } else {
      int *ptr = va_arg(*arg_list, int *);
      *ptr = value;
    }
  }
  if (!success) {
    *shift = 0;
  }
}

void s21_ReadAndAssignDouble(va_list *const arg_list,
                             const Format *const format, const char *str,
                             int *const shift) {
  /* printf("Double\n"); */
  long double value = s21_atold(str, 1, shift, format->width);
  if (!format->suppress_assignment && *shift) {
    if (format->length == 'L') {
      long double *ptr = va_arg(*arg_list, long double *);
      *ptr = value;
    } else if (format->length == 'l') {
      double *ptr = va_arg(*arg_list, double *);
      *ptr = value;
    } else {
      float *ptr = va_arg(*arg_list, float *);
      *ptr = value;
    }
  }
}

void s21_ReadAndAssignString(va_list *const arg_list,
                             const Format *const format, const char *str,
                             int *const shift) {
  char *ptr = S21_NULL;
  int alloc = 0;
  if (format->suppress_assignment) {
    ptr = calloc(1, TMP_STR_SIZE);
    alloc = 1;
  } else {
    ptr = va_arg(*arg_list, char *);
  }
  int max_char = format->width;
  if (format->value_type == 'C') {
    s21_strcpyn(str, ptr, &max_char, format->length == 'l');
  } else if (format->value_type == 'S') {
    s21_strcpynws(str, ptr, &max_char, shift, format->length == 'l');
  }
  *shift += format->width - max_char;
  if (alloc) {
    free(ptr);
  }
}

void s21_AssignValue(va_list *const arg_list, const Format *const format,
                     const char *str, int *const shift,
                     const int total_symbols) {
  char fmt = format->value_type;
  if (fmt == 'U' || fmt == 'I' || fmt == 'D' || fmt == 'X' || fmt == 'O' ||
      fmt == 'N') {
    s21_ReadAndAssignInt(arg_list, format, str, shift, total_symbols);
  } else if (fmt == 'E') {
    s21_ReadAndAssignDouble(arg_list, format, str, shift);
  } else if (fmt == 'S' || fmt == 'C') {
    s21_ReadAndAssignString(arg_list, format, str, shift);
  } else if (fmt == '%') {
    while (isspace(*str)) {
      ++str;
      ++(*shift);
    }
    *shift += *str == '%';
  }
}

int s21_sscanf(const char *str, const char *format, ...) {
  int assigned_arg_count = 0, total_symbols_read = 0, error = 0;
  error = format == S21_NULL ? 1 : 0;
  assigned_arg_count = format == S21_NULL ? -1 : 0;
  va_list arg_list;
  va_start(arg_list, format);
  while (!error && *format) {
    if (isspace(*format)) {
      while (isspace(*str)) {
        ++str;
        ++total_symbols_read;
      }
      ++format;
    } else if (*format == '%') {
      int format_len = 0;
      Format f = s21_ParseFormatSpecifier(format, &format_len, 0);
      format += format_len + 1;
      /* printf("Sscanf source before: %s\n", str); */
      int shift = 0;
      s21_AssignValue(&arg_list, &f, str, &shift, total_symbols_read);
      assigned_arg_count +=
          shift > 0 && f.value_type != '%' && !f.suppress_assignment;
      str += shift;
      /* printf("Sscanf source after: %s\n", str); */
      total_symbols_read += shift;
      error = shift == 0 && f.value_type != 'N';
    } else {
      if (*str == *format) {
        ++str;
        ++format;
        ++total_symbols_read;
      } else {
        error = 1;
      }
    }
  }
  va_end(arg_list);

  return assigned_arg_count;
}

void *s21_insert(const char *into, const char *str, s21_size_t start_index) {
  int error = 0;
  char *new_string = S21_NULL;
  s21_size_t into_len = 0;
  s21_size_t str_len = 0;
  if (into && str && !(start_index > (into_len = s21_strlen(into)))) {
    str_len = s21_strlen(str);
    new_string = (char *)calloc(1, into_len + str_len + 1);
    if (new_string) {
      int char_to_copy = (s21_size_t)start_index;
      s21_strcpyn(into, new_string, &char_to_copy, 0);
      char_to_copy = str_len;
      s21_strcpyn(str, new_string + start_index, &char_to_copy, 0);
      char_to_copy = into_len - start_index;
      s21_strcpyn(into + start_index, new_string + start_index + str_len,
                  &char_to_copy, 0);
    }
  }
  return error ? S21_NULL : new_string;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *new_string = S21_NULL;
  if (src && trim_chars) {
    int len_src = s21_strlen(src);
    int len_trim = s21_strlen(trim_chars);
    new_string = (char *)calloc(1, len_src + 1);
    int new_start = 0, new_end = len_src - 1;
    if (len_trim > 0) {
      while (new_start < len_src && s21_AnyOf(src[new_start], trim_chars)) {
        ++new_start;
      }
      while (new_end >= 0 && s21_AnyOf(src[new_end], trim_chars)) {
        --new_end;
      }
    } else {
      while (new_start < len_src && isspace(src[new_start])) {
        ++new_start;
      }
      while (new_end >= 0 && isspace(src[new_end])) {
        --new_end;
      }
    }
    if (new_string) {
      int char_to_copy = new_end - new_start + 1;
      s21_strcpyn(src + new_start, new_string, &char_to_copy, 0);
    }
  }
  return new_string;
}
