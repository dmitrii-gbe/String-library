#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "s21_string.h"

int IsNegativeLongDouble(long double val) {
  s21_size_t *ptr = (s21_size_t *)&val + 1;
  s21_size_t copy = *ptr;
  s21_size_t m = 1;
  m = m << 15;
  copy &= m;
  return copy == m;
}

char GetDigit(const unsigned int num, const int base) {
  char result;
  if (base <= 10 || num < 10) {
    result = num + '0';
  } else {
    result = num + 55;
  }
  return result;
}

void Swap(char *const c1, char *const c2) {
  char tmp = *c2;
  *c2 = *c1;
  *c1 = tmp;
}

void Reverse(char *const str) {
  s21_size_t end = s21_strlen(str) - 1;
  s21_size_t start = 0;
  while (end > start) {
    Swap(str + start++, str + end--);
  }
}

char *s21_Itoa_Inner(unsigned long long val, const int base) {
  char *buffer = calloc(1, BUFFER_SIZE);
  s21_size_t cursor = 0;
  if (val == 0) {
    buffer[cursor++] = '0';
  }
  while (val != 0) {
    unsigned int num = val % base;
    val /= base;
    buffer[cursor++] = GetDigit(num, base);
  }
  if (base == 8) {
    *(buffer + cursor++) = '0';
  } else if (base == 16) {
    *(buffer + cursor++) = 'x';
    *(buffer + cursor++) = '0';
  }
  Reverse(buffer);
  return buffer;
}

char *s21_Itoa(long long val, const int base) {
  int negative = 0;
  if (val < 0) {
    negative = 1;
    val = -val;
  }
  char *tmp = s21_Itoa_Inner(val, base);
  char *result;
  if (negative) {
    result = s21_insert(tmp, "-", 0);
    free(tmp);
  } else {
    result = tmp;
  }
  return result;
}

void AssignNewDigit(int *const in_mind, char *const c, const int add_in_mind) {
  int new_digit = *c - '0' + (add_in_mind ? *in_mind : 1);
  *c = (new_digit % 10) + '0';
  *in_mind = new_digit / 10;
}

void Round(char *const num_str, const int precision) {
  int len = s21_strlen(num_str);
  int point_index = 0;
  int found = 0;
  for (int i = 0; i < len && !found; ++i) {
    if (num_str[i] == '.') {
      found = 1;
      point_index = i;
    }
  }
  int last_index = precision == 0 ? point_index - 1 : point_index + precision;
  int in_mind = 0, i = len - 2;
  for (; i >= last_index; --i) {
    if (num_str[i] != '.') {
      int prev_digit_index = num_str[i + 1] == '.' ? i + 2 : i + 1;
      if (num_str[prev_digit_index] > '5' ||
          (num_str[prev_digit_index] == 5 && (num_str[i] - '0') % 2 != 0)) {
        AssignNewDigit(&in_mind, num_str + i, 0);
      } else {
        AssignNewDigit(&in_mind, num_str + i, 1);
      }
      num_str[prev_digit_index] = '0';
    }
  }
  num_str[point_index + precision + 1] = '\0';
  while (i >= 0 && in_mind) {
    if (num_str[i] != '.') {
      AssignNewDigit(&in_mind, num_str + i, 0);
    }
    --i;
  }
  if (in_mind) {
    char *tmp = s21_insert(num_str, "1", 0);
    s21_strcpy(tmp, num_str);
    free(tmp);
  }
}

int Log10(long double val) {
  int degree = 0;
  while (val >= 10.0) {
    ++degree;
    val /= 10.0L;
  }
  return degree;
}

char *GetIntegerPartOfDouble(long double val, long double *const fraction) {
  int number_of_digits = Log10(val) + 1;
  char *buffer = calloc((s21_size_t)number_of_digits + 1, 1);
  s21_size_t cursor = 0;
  long double max_pow = s21_Pow(10.0, number_of_digits - 1);
  while (number_of_digits) {
    --number_of_digits;
    int digit = (int)(val / max_pow);
    buffer[cursor++] = digit + '0';
    val -= max_pow * (long double)digit;
    max_pow /= 10.0L;
  }
  *fraction = val;
  buffer[cursor] = '\0';
  return buffer;
}

char *s21_Itof(long double val) {
  int negative = 0;
  if (val < 0) {
    negative = 1;
    val = -val;
  }
  char *result = S21_NULL;
  if (!isnan(val) && !isinf(val)) {
    long double fraction;
    char *integer = GetIntegerPartOfDouble(val, &fraction);
    char mantissa[BUFFER_SIZE];
    int index = 0;
    for (; index < BUFFER_SIZE / 2;) {
      fraction *= 10;
      mantissa[index] = '0' + (int)fraction;
      fraction -= (long double)(mantissa[index++] - '0');
    }
    mantissa[index] = '\0';
    char *tmp = calloc(1, BUFFER_SIZE);
    result = tmp;
    if (negative) {
      *tmp++ = '-';
    }
    s21_strcpy(integer, tmp);
    s21_strcpy(".", tmp + s21_strlen(integer));
    s21_strcpy(mantissa, tmp + s21_strlen(integer) + 1);
    free(integer);
    /* printf("%d\n", precision); */
    /* Round(result, precision); */
  } else if (isnan(val)) {
    result = calloc(4, 1);
    s21_strcpy("nan", result);
    NativeInsert(&result, (IsNegativeLongDouble(val) ? "-" : ""), 0);
  } else if (isinf(val)) {
    result = calloc(5, 1);
    s21_strcpy("inf", result);
    NativeInsert(&result, (negative ? "-" : ""), 0);
  }
  return result;
}

int s21_strcmp(const char *str1, const char *str2) {
  int result = 0;
  while (*str1 && *str2 && *str1 == *str2) {
    ++str1;
    ++str2;
  }
  if (*str1 > *str2) {
    result = 1;
  } else if (*str2 > *str1) {
    result = -1;
  }
  return result;
}

void NativeInsert(char **const to, const char *const from,
                  const s21_size_t position) {
  char *tmp = s21_insert(*to, from, position);
  free(*to);
  *to = tmp;
}

char *GetUniformString(const char c, const s21_size_t count) {
  char *str = calloc(count + 1, 1);
  for (s21_size_t i = 0; i < count; ++i) {
    str[i] = c;
  }
  str[count] = '\0';
  return str;
}

void AdjustFormatAccuracyAndWidth(Format *const f, va_list *arg_list) {
  if (f->width == ASTERISK) {
    f->width = va_arg(*arg_list, int);
  }
  if (f->accuracy == ASTERISK) {
    f->accuracy = va_arg(*arg_list, int);
  }
}

void ProcessDecimalIntString(char **const str_ptr, Format *const format) {
  int is_zero = s21_strlen(*str_ptr) == 1 && (*str_ptr)[0] == '0' &&
                format->accuracy == 0;
  char *processed_str = calloc(is_zero ? 1 : s21_strlen(*str_ptr) + 1, 1);
  s21_strcpy(is_zero ? "" : *str_ptr, processed_str);
  /* printf("ProcessDecimalString %s\n", processed_str); */
  int is_negative = processed_str[0] == '-';

  if (format->flags['+'] && !is_negative) {
    NativeInsert(&processed_str, "+", 0);
  }

  int len =
      s21_strlen(processed_str) - (is_negative || (processed_str[0] == '+'));

  if (format->flags[' '] && !is_negative && format->value_type != 'u') {
    NativeInsert(&processed_str, " ", 0);
  }

  if (format->accuracy != -1 && format->accuracy > len) {
    char *to_insert = GetUniformString('0', format->accuracy - len);
    NativeInsert(
        &processed_str, to_insert,
        (is_negative || processed_str[0] == '+' || processed_str[0] == ' ')
            ? 1
            : 0);
    free(to_insert);
  }

  if (format->width != INT_MAX &&
      (s21_size_t)format->width > s21_strlen(processed_str)) {
    char *to_insert =
        GetUniformString(format->flags['0'] ? '0' : ' ',
                         format->width - s21_strlen(processed_str));
    NativeInsert(
        &processed_str, to_insert,
        (format->flags['-'] ? s21_strlen(processed_str)
         : ((is_negative || format->flags['+'] || format->flags[' ']) &&
            format->flags['0'])
             ? 1
             : 0));
    free(to_insert);
  }
  free(*str_ptr);

  *str_ptr = processed_str;
}

void ProcessHexadecimalIntString(char **const str_ptr, Format *const format) {
  int is_zero_value = s21_strlen(*str_ptr) == 3 && (*str_ptr)[2] == '0';
  int is_zero = is_zero_value && format->accuracy == 0;
  char *processed_str = calloc(is_zero ? 1 : s21_strlen(*str_ptr) + 1, 1);
  s21_strcpy(
      (is_zero ? ""
               : ((*str_ptr) + (format->flags['#'] && !is_zero_value ? 0 : 2))),
      processed_str);

  int len = s21_strlen(processed_str) -
            (format->flags['#'] && !is_zero && !is_zero_value ? 2 : 0);
  if (format->accuracy != -1 && format->accuracy > len) {
    char *to_insert = GetUniformString('0', format->accuracy - len);
    NativeInsert(&processed_str, to_insert,
                 (format->flags['#'] && !is_zero_value ? 2 : 0));
    free(to_insert);
  }

  if (format->width != INT_MAX &&
      (s21_size_t)format->width > s21_strlen(processed_str)) {
    char *to_insert =
        GetUniformString(format->flags['0'] ? '0' : ' ',
                         format->width - s21_strlen(processed_str));
    NativeInsert(&processed_str, to_insert,
                 (format->flags['-'] ? s21_strlen(processed_str)
                                     : (format->flags['#'] && !is_zero_value &&
                                                format->flags['0']
                                            ? 2
                                            : 0)));
    free(to_insert);
  }

  if (format->value_type == 'X') {
    s21_ToUpperInternal(processed_str);
  } else {
    s21_ToLowerInternal(processed_str);
  }
  free(*str_ptr);

  *str_ptr = processed_str;
}

void ProcessOctalIntString(char **const str_ptr, Format *const format) {
  int is_zero_value = s21_strlen(*str_ptr) == 2 && (*str_ptr)[1] == '0';
  int is_zero = is_zero_value && format->accuracy == 0;
  char *processed_str = calloc(is_zero ? 2 : s21_strlen(*str_ptr) + 1, 1);
  s21_strcpy(
      (is_zero ? (format->flags['#'] ? "0" : "")
               : ((*str_ptr) + (format->flags['#'] && !is_zero_value ? 0 : 1))),
      processed_str);

  int len = s21_strlen(processed_str) - (format->flags['#'] ? 1 : 0);
  if (format->accuracy != -1 && format->accuracy > len) {
    char *to_insert =
        GetUniformString('0', format->accuracy - len - format->flags['#']);
    NativeInsert(&processed_str, to_insert,
                 (format->flags['#'] && !is_zero_value ? 1 : 0));
    free(to_insert);
  }

  if (format->width != INT_MAX &&
      (s21_size_t)format->width > s21_strlen(processed_str)) {
    char *to_insert =
        GetUniformString(format->flags['0'] ? '0' : ' ',
                         format->width - s21_strlen(processed_str));
    NativeInsert(&processed_str, to_insert,
                 (format->flags['-'] ? s21_strlen(processed_str)
                                     : (format->flags['#'] && !is_zero_value &&
                                                format->flags['0']
                                            ? 1
                                            : 0)));
    free(to_insert);
  }

  free(*str_ptr);
  *str_ptr = processed_str;
}

char *GetIntString(va_list *const arg_list, Format *const format) {
  AdjustFormatAccuracyAndWidth(format, arg_list);
  char *tmp = S21_NULL;
  char fmt = format->value_type;
  if (fmt == 'd' || fmt == 'i') {
    if (format->length == 'l') {
      tmp = s21_Itoa(va_arg(*arg_list, long), 10);
    } else {
      tmp = s21_Itoa(va_arg(*arg_list, int), 10);
    }
    ProcessDecimalIntString(&tmp, format);
  } else if (fmt == 'u') {
    if (format->length == 'l') {
      unsigned long val = va_arg(*arg_list, unsigned long);
      tmp = s21_Itoa_Inner(val, 10);
    } else {
      unsigned val = va_arg(*arg_list, unsigned);
      tmp = s21_Itoa_Inner(val, 10);
    }
    ProcessDecimalIntString(&tmp, format);
  } else if (fmt == 'x' || fmt == 'X') {
    if (format->length == 'l') {
      tmp = s21_Itoa_Inner(va_arg(*arg_list, long unsigned), 16);
    } else {
      tmp = s21_Itoa_Inner(va_arg(*arg_list, unsigned), 16);
    }
    ProcessHexadecimalIntString(&tmp, format);
  } else if (fmt == 'o') {
    if (format->length == 'l') {
      tmp = s21_Itoa_Inner(va_arg(*arg_list, long unsigned), 8);
    } else {
      tmp = s21_Itoa_Inner(va_arg(*arg_list, unsigned), 8);
    }
    ProcessOctalIntString(&tmp, format);
  }
  return tmp;
}

int IsIntValueType(const char c) {
  return c == 'u' || c == 'i' || c == 'd' || c == 'o' || c == 'x' || c == 'X';
}

s21_size_t s21_wcslen(const wchar_t *str) {
  s21_size_t counter = 0;
  while (*str != L'\0') {
    ++counter;
    ++str;
  }
  return counter;
}

char *GetWChar(va_list *const arg_list, Format *const format) {
  AdjustFormatAccuracyAndWidth(format, arg_list);
  wchar_t wch = 0;
  char *result = S21_NULL;
  char c;

  if (format->length == 'l') {
    wch = va_arg(*arg_list, wint_t);
    mbstate_t state;
    s21_memset(&state, 0, sizeof(state));
    result = calloc(10, sizeof(char));
    int size = wcrtomb(result, wch, &state);
    result[size] = '\0';
  } else {
    c = va_arg(*arg_list, int);
    result = calloc(2, sizeof(char));
    result[0] = c;
    result[1] = '\0';
  }

  if (format->width != INT_MAX && format->width > 1) {
    char *to_insert = GetUniformString(' ', format->width - s21_strlen(result));
    NativeInsert(&result, to_insert,
                 format->flags['-'] ? s21_strlen(result) : 0);
    free(to_insert);
  }

  return result;
}

char *GetWString(va_list *const arg_list, Format *const format) {
  AdjustFormatAccuracyAndWidth(format, arg_list);
  wchar_t *wstr = S21_NULL;
  char *str = S21_NULL;
  char *result = S21_NULL;

  if (format->length == 'l') {
    wstr = va_arg(*arg_list, wchar_t *);
    s21_size_t wlen = s21_wcslen(wstr);
    result = calloc(wlen * 10, sizeof(char));
    char *cursor = result;
    wcstombs(cursor, wstr,
             format->accuracy != -1 ? (s21_size_t)format->accuracy : wlen * 10);
  } else {
    str = va_arg(*arg_list, char *);
    result = calloc(s21_strlen(str) + 1, 1);
    s21_strcpy(str, result);
    result[format->accuracy != -1 &&
                   (s21_size_t)format->accuracy < s21_strlen(result)
               ? (s21_size_t)format->accuracy
               : s21_strlen(result)] = '\0';
  }
  s21_size_t len = s21_strlen(result);
  if (format->width != INT_MAX && (s21_size_t)format->width > len) {
    char *to_insert = GetUniformString(' ', format->width - len);
    NativeInsert(&result, to_insert, format->flags['-'] ? len : 0);
    free(to_insert);
  }

  return result;
}

int CheckIfZeroDoubleString(const char *str) {
  int result = 1;
  while (*str) {
    if (s21_AnyOf(*str, "123456789")) {
      result = 0;
    }
    ++str;
  }
  return result;
}

char *FindFirstChar(const char *str, const char *set) {
  int found = 0;
  while (*str && !found) {
    if (s21_AnyOf(*str, set)) {
      found = 1;
      --str;
    }
    ++str;
  }
  return (char *)str;
}

void RemoveCharacter(char *str, const char *const ptr) {
  while (str != ptr) {
    ++str;
  }
  char *new = (char *)ptr + 1;
  s21_strcpy(new, str);
}

void ProcessDoubleStringF(char **const str_ptr, Format *const format,
                          const int from_g_style) {
  s21_size_t len = s21_strlen(*str_ptr);
  int is_negative = (*str_ptr)[0] == '-';
  if ((*str_ptr)[len - 1] == '.' && !format->flags['#']) {
    (*str_ptr)[len - 1] = 0;
  } else if (((*str_ptr)[len - 1] == '.' && format->flags['#']) &&
             !from_g_style) {
    NativeInsert(str_ptr, "0", len);
  }

  NativeInsert(
      str_ptr,
      format->flags['+'] && !is_negative && (*str_ptr)[0] != '-' ? "+" : "", 0);
  NativeInsert(
      str_ptr,
      format->flags[' '] && !is_negative && (*str_ptr)[0] != '-' ? " " : "", 0);
  len = s21_strlen(*str_ptr);
  if (format->width != INT_MAX && (s21_size_t)format->width > len) {
    char *to_insert =
        GetUniformString(format->flags['0'] ? '0' : ' ', format->width - len);
    NativeInsert(str_ptr, to_insert,
                 format->flags['-']                                        ? len
                 : format->flags['+'] || format->flags[' '] || is_negative ? 1
                                                                           : 0);
    free(to_insert);
  }
}

void DoExtraProcessingDoubleE(char **const str_ptr, Format *const format,
                              int degree, char *suffix, int is_negative) {
  s21_size_t len = s21_strlen(*str_ptr);
  suffix[0] = format->value_type;
  s21_sprintf(suffix + 1, "%+.2d", degree);
  char *new_str = calloc(s21_strlen(*str_ptr) + s21_strlen(suffix) + 1, 1);
  s21_strcpy(*str_ptr, new_str);
  s21_strcpy(suffix, new_str + s21_strlen(*str_ptr));
  char *tmp = *str_ptr;
  *str_ptr = new_str;
  free(tmp);
  NativeInsert(
      str_ptr,
      format->flags['+'] && !is_negative && (*str_ptr)[0] != '-' ? "+" : "", 0);
  NativeInsert(
      str_ptr,
      format->flags[' '] && !is_negative && (*str_ptr)[0] != '-' ? " " : "", 0);
  len = s21_strlen(*str_ptr);
  if (format->width != INT_MAX && (s21_size_t)format->width > len) {
    char *to_insert =
        GetUniformString(format->flags['0'] ? '0' : ' ', format->width - len);
    NativeInsert(str_ptr, to_insert,
                 format->flags['-'] ? len
                 : (format->flags['+'] || format->flags[' '] || is_negative) &&
                         format->flags['0']
                     ? 1
                     : 0);
    free(to_insert);
  }
}

void ProcessDoubleStringE(char **const str_ptr, Format *const format) {
  int is_zero = CheckIfZeroDoubleString(*str_ptr), is_negative = 0, degree = 0;
  char *first_point = S21_NULL;
  char *second_point = S21_NULL;
  char suffix[10];
  if (!is_zero) {
    is_negative = (*str_ptr)[0] == '-';
    char *first_non_zero_position = FindFirstChar(*str_ptr, "123456789");
    char *point_position = FindFirstChar(*str_ptr, ".");
    int distance = point_position - first_non_zero_position;
    degree = distance > 0 ? distance - 1 : distance;
    NativeInsert(str_ptr, ".", first_non_zero_position - (*str_ptr) + 1);
    first_point = FindFirstChar(*str_ptr, ".");
    second_point = FindFirstChar(first_point + 1, ".");
    RemoveCharacter(*str_ptr, degree < 0 ? first_point : second_point);
    char *from = FindFirstChar(*str_ptr, "-123456789");
    s21_strcpy(from, *str_ptr);
    Round(*str_ptr, format->accuracy);
  } else {
    Round(*str_ptr, format->accuracy);
  }
  first_point = FindFirstChar(*str_ptr, ".");
  if (format->accuracy == 0 && !format->flags['#']) {
    *first_point = '\0';
  }
  DoExtraProcessingDoubleE(str_ptr, format, degree, suffix, is_negative);
}

void ProcessTrailingZeroes(char *const str) {
  char *point_ptr = FindFirstChar(str, ".");
  char *exp_ptr = FindFirstChar(str, "Ee");
  char *ptr = exp_ptr - 1;
  if (*point_ptr != '\0') {
    int found = 0;
    for (; ptr != point_ptr && !found;) {
      if (*ptr != '0') {
        found = 1;
        ++ptr;
      }
      --ptr;
    }
    s21_strcpy(exp_ptr, ptr + (ptr != point_ptr));
  }
}

int IsNonNumericValue(const char *const str) {
  int result = 0;
  result = s21_strcmp(str, "inf") == 0 || s21_strcmp(str, "-inf") == 0 ||
           s21_strcmp(str, "nan") == 0 || s21_strcmp(str, "-nan") == 0;

  return result;
}

void ProcessNAN(char **const str_ptr) {
  if (s21_AnyOf(**str_ptr, "-+") && (s21_strcmp((*str_ptr) + 1, "nan") == 0 ||
                                     s21_strcmp((*str_ptr) + 1, "NAN") == 0)) {
    RemoveCharacter(*str_ptr, *str_ptr);
  }
}

void ProcessDoubleString(char **const str_ptr, Format *const format,
                         const int from_g_style) {
  if (IsNonNumericValue(*str_ptr)) {
    if (format->flags['+'] && (*str_ptr)[0] != '-') {
      NativeInsert(str_ptr, "+", 0);
    }
    if (format->value_type < 96) {
      s21_ToUpperInternal(*str_ptr);
    }
#if defined(__APPLE__)
    ProcessNAN(str_ptr);
#endif
    char *result = calloc(s21_strlen(*str_ptr) + 1, 1);
    s21_strcpy(*str_ptr, result);
    s21_size_t len = s21_strlen(result);
    if (format->width != INT_MAX && (s21_size_t)format->width > len) {
      char *to_insert = GetUniformString(' ', format->width - len);
      NativeInsert(&result, to_insert, format->flags['-'] ? len : 0);
      free(to_insert);
    }
    char *tmp = *str_ptr;
    *str_ptr = result;
    free(tmp);
  } else if (s21_AnyOf(format->value_type, "fF")) {
    Round(*str_ptr, format->accuracy);
    ProcessDoubleStringF(str_ptr, format, from_g_style);
  } else if (s21_AnyOf(format->value_type, "eE")) {
    ProcessDoubleStringE(str_ptr, format);
  } else if (s21_AnyOf(format->value_type, "gG")) {
    char *copy = calloc(s21_strlen(*str_ptr) + 1, 1);
    s21_strcpy(*str_ptr, copy);
    ProcessDoubleStringE(&copy, format);
    char *ptr = FindFirstChar(copy, "gG");
    int shift = 0, success = 0;
    int degree = s21_atol(ptr + 2, 10, &shift, INT_MAX, &success);
    free(copy);
    if (degree < -4 || degree >= format->accuracy) {
      format->value_type = format->value_type == 'G' ? 'E' : 'e';
      format->accuracy -= 1;
    } else {
      format->value_type = format->value_type == 'G' ? 'F' : 'f';
      if (degree > 0) {
        format->accuracy -= (degree + 1);
      }
      if (degree <= 0) {
        --format->accuracy;
      }
    }
    ProcessDoubleString(str_ptr, format, 1);
    if (!format->flags['#']) {
      ProcessTrailingZeroes(*str_ptr);
    }
  }
}

char *GetDoubleString(va_list *const arg_list, Format *const format) {
  AdjustFormatAccuracyAndWidth(format, arg_list);
  char *result = S21_NULL;
  if (format->length == 'L') {
    long double val = va_arg(*arg_list, long double);
    result = s21_Itof(val);
  } else {
    double val = va_arg(*arg_list, double);
    result = s21_Itof(val);
  }
  ProcessDoubleString(&result, format, 0);
  return result;
}

char *GetValueString(va_list *const arg_list, Format *const format,
                     const int total_char_written) {
  char *result = S21_NULL;
  char fmt = format->value_type;
  if (IsIntValueType(fmt)) {
    result = GetIntString(arg_list, format);
  } else if (fmt == '%') {
    result = GetUniformString('%', 1);
  } else if (fmt == 'n') {
    int *ptr = va_arg(*arg_list, int *);
    *ptr = total_char_written;
    result = calloc(1, 1);
  } else if (fmt == 's') {
    result = GetWString(arg_list, format);
  } else if (fmt == 'c') {
    result = GetWChar(arg_list, format);
  } else if (fmt == 'n') {
    int *ptr = va_arg(*arg_list, int *);
    *ptr = total_char_written;
    result = calloc(1, 1);
  } else if (s21_AnyOf(fmt, "eEfFgG")) {
    result = GetDoubleString(arg_list, format);
  }
  return result;
}

int s21_sprintf(char *str, const char *format, ...) {
  /* int assigned_arg_count = 0; */
  int total_symbols_written = 0;
  va_list arg_list;
  va_start(arg_list, format);
  int error = 0;
  error = format == S21_NULL ? 1 : 0;
  total_symbols_written = format == S21_NULL ? -1 : 0;
  while (!error && *format) {
    if (*format == '%') {
      int format_len = 0;
      Format f = s21_ParseFormatSpecifier(format, &format_len, 1);
      format += format_len + 1;
      char *to_write = GetValueString(&arg_list, &f, total_symbols_written);
      s21_strcpy(to_write, str);
      int len = s21_strlen(to_write);
      free(to_write);
      total_symbols_written += len;
      str += len;
    } else {
      while (*format && *format != '%') {
        *str++ = *format++;
        ++total_symbols_written;
      }
    }
  }
  *str = '\0';
  va_end(arg_list);
  return total_symbols_written;
}

/*void LongDoubleTest() {
  long double val_double = 93456789.9955666666435673456783245678435678e15L;
  char st[10000];
  printf("%d\n", val_double < 0);
  sprintf(st, "%23.6Lf", val_double);
  char *str3 = s21_Itof(val_double);
  Round(str3, 6);
  printf("%s\n", st);
  printf("%s\n", str3);
  assert(s21_strcmp(st, str3) == 0);
  free(str3);
}

int main() {
  LongDoubleTest();
  long double val_double = 93456789.9955666666435673456783245678435678e-3L;

  long double val_double1 = 63.9955666666435673456783245678435678e-15L;
  long double val_double2 = -43.8e15L;
  long double val_double3 = 1.0L;
  long double val_double4 = 1.0L / 0.0L;
  long double val_double5 = -val_double4;
  long double val_double6 = sqrt(-5.0L);
  long double val_double7 = -sqrt(-5.0L);
#define FORMAT_DOUBLE                                                 \
  "start  %10LE %#10LE %10.0LE %#10.0LE %10.3LE %#10.3LE %#+023.0Le " \
  "%+023.0Le %+-.6LE "                                                \
  "%-+20.Lf %+021.6LF "                                               \
  "\n%#+.3Lg %+.3Lg\n %#+.10Lg  "                                     \
  "\n%#+.0Lg %+.0Lg\n "                                               \
  "%+.6LE %.6Lg "                                                     \
  "%.6Lf "                                                            \
  "%.6Le "                                                            \
  "end"
#define ARG_LIST_DOUBLE                                                       \
  val_double, val_double, val_double, val_double, val_double, val_double,     \
      val_double, val_double, val_double, val_double, val_double, val_double, \
      val_double, val_double, val_double, val_double, val_double, val_double, \
      val_double, val_double
#define ARG_LIST_DOUBLE1                                               \
  val_double1, val_double1, val_double1, val_double1, val_double1,     \
      val_double1, val_double1, val_double1, val_double1, val_double1, \
      val_double1, val_double1, val_double1, val_double1, val_double1, \
      val_double1, val_double1, val_double1, val_double1, val_double1
#define ARG_LIST_DOUBLE2                                               \
  val_double2, val_double2, val_double2, val_double2, val_double2,     \
      val_double2, val_double2, val_double2, val_double2, val_double2, \
      val_double2, val_double2, val_double2, val_double2, val_double2, \
      val_double2, val_double2, val_double2, val_double2, val_double2
#define ARG_LIST_DOUBLE3                                               \
  val_double3, val_double3, val_double3, val_double3, val_double3,     \
      val_double3, val_double3, val_double3, val_double3, val_double3, \
      val_double3, val_double3, val_double3, val_double3, val_double3, \
      val_double3, val_double3, val_double3, val_double3, val_double3
#define ARG_LIST_DOUBLE4                                               \
  val_double4, val_double5, val_double6, val_double7, val_double4,     \
      val_double5, val_double6, val_double7, val_double4, val_double5, \
      val_double6, val_double7, val_double4, val_double5, val_double6, \
      val_double7, val_double4, val_double5, val_double6, val_double7
  char str[10000] = {0};
  char str1[10000] = {0};
  char str_1[10000] = {0};
  char str1_1[10000] = {0};
  char str_2[10000] = {0};
  char str1_2[10000] = {0};
  char str_3[10000] = {0};
  char str1_3[10000] = {0};
  char str_4[10000] = {0};
  char str1_4[10000] = {0};
  sprintf(str, FORMAT_DOUBLE, ARG_LIST_DOUBLE);
  s21_sprintf(str1, FORMAT_DOUBLE, ARG_LIST_DOUBLE);
  sprintf(str_1, FORMAT_DOUBLE, ARG_LIST_DOUBLE1);
  s21_sprintf(str1_1, FORMAT_DOUBLE, ARG_LIST_DOUBLE1);
  sprintf(str_2, FORMAT_DOUBLE, ARG_LIST_DOUBLE2);
  s21_sprintf(str1_2, FORMAT_DOUBLE, ARG_LIST_DOUBLE2);
  sprintf(str_3, FORMAT_DOUBLE, ARG_LIST_DOUBLE3);
  s21_sprintf(str1_3, FORMAT_DOUBLE, ARG_LIST_DOUBLE3);
  sprintf(str_4, FORMAT_DOUBLE, ARG_LIST_DOUBLE4);
  s21_sprintf(str1_4, FORMAT_DOUBLE, ARG_LIST_DOUBLE4);
  assert(s21_strcmp(str1, str) == 0);
  assert(s21_strcmp(str1_1, str_1) == 0);
  assert(s21_strcmp(str1_2, str_2) == 0);
  assert(s21_strcmp(str1_3, str_3) == 0);
  assert(s21_strcmp(str1_4, str_4) == 0);
  return 0;
}*/
