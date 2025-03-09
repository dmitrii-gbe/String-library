#pragma once

#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define TMP_STR_SIZE 10000
#define BUFFER_SIZE 9000
#define DEFAULT_ACCURACCY 6
#define INITIAL_PRECISION 5000
#define ASTERISK INT_MIN
#define SIGN_BIT_INDEX 79

#define S21_NULL (void *)0
typedef unsigned long s21_size_t;

typedef struct FormatSpecifier {
  int suppress_assignment;
  char value_type;
  char length;
  int width;
  int flags['0' + 1];
  int accuracy;
} Format;

long long s21_atol(const char *const str, const int base, int *const shift,
                   int max_char, int *const success);
long double s21_atold(const char *const str, const int parse_exponent,
                      int *const shift, int max_char);
void s21_strcpy(const char *from, char *to);
void s21_strcpyn(const char *from, char *to, int *const max_char,
                 const int wchar);
void s21_strcpynws(const char *from, char *to, int *const max_char,
                   int *const preceeding_ws, const int wchar);
void s21_ToUpperInternal(char *const str);
void s21_ToLowerInternal(char *const str);
void s21_AssignProceedVariable(const char c, const int base,
                               int *const proceed);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
int s21_sscanf(const char *str, const char *format, ...);
Format s21_ParseFormatSpecifier(const char *str, int *const format_len,
                                const int sprintf);
void s21_InitializeFormat(Format *const f);
int s21_IsDigit(const char c);
int s21_AnyOf(const char c, const char *str);
int s21_IsExtraHexadecimalDigit(const char c);
int s21_GetRadix(const char *str);
void s21_AssignValue(va_list *const arg_list, const Format *const format,
                     const char *str, int *const shift,
                     const int total_symbols);
void s21_ReadAndAssignInt(va_list *const arg_list, const Format *const format,
                          const char *str, int *const shift,
                          const int total_symbols);
void s21_ReadAndAssignDouble(va_list *const arg_list,
                             const Format *const format, const char *str,
                             int *const shift);
void s21_ReadAndAssignString(va_list *const arg_list,
                             const Format *const format, const char *str,
                             int *const shift);
int s21_Log(long num, const int base);
long double s21_Pow(const int base, int degree);
long double s21_Fabsl(long double val);
void *s21_insert(const char *into, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
char *s21_Itoa(long long val, const int base);
char *s21_Itoa_Inner(unsigned long long val, const int base);
char GetDigit(const unsigned int num, const int base);
void Reverse(char *const str);
void Swap(char *const c1, char *const c2);
char *s21_Itof(long double val);
void Round(char *const num_str, const int precision);
void AssignNewDigit(int *const in_mind, char *const c, const int add_in_mind);
int s21_strcmp(const char *str1, const char *str2);
void AdjustFormat(Format *const f, int sprintf);
int s21_sprintf(char *str, const char *format, ...);
void ProcessDecimalIntString(char **const str_ptr, Format *const format);
char *GetIntString(va_list *const arg_list, Format *const format);
void NativeInsert(char **const to, const char *const from,
                  const s21_size_t position);
char *GetUniformString(const char c, const s21_size_t count);
int IsIntValueType(const char c);
void ProcessHexadecimalIntString(char **const str_ptr, Format *const format);
void ProcessOctalIntString(char **const str_ptr, Format *const format);
char *GetValueString(va_list *const arg_list, Format *const format,
                     const int total_char_written);
void AdjustFormatAccuracyAndWidth(Format *const f, va_list *arg_list);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
int s21_strncmp(const char *str1, const char *str2, s21_size_t volume);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
void *s21_memchr(const void *str, int c, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
int Log10(long double val);
char *GetIntegerPartOfDouble(long double val, long double *const fraction);
void ProcessOctalIntString(char **const str_ptr, Format *const format);
int IsNegativeLongDouble(long double val);
s21_size_t s21_wcslen(const wchar_t *str);
char *GetWString(va_list *const arg_list, Format *const format);
char *GetWChar(va_list *const arg_list, Format *const format);
int is_delimiter(char c, const char *delim);
char *s21_strchr(const char *str, int c);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strtok(char *str, const char *delim);
char *GetDoubleString(va_list *const arg_list, Format *const format);
void ProcessDoubleString(char **const str_ptr, Format *const format,
                         const int from_g_style);
void ProcessDoubleStringF(char **const str_ptr, Format *const format,
                          const int from_g_style);
void ProcessDoubleStringE(char **const str_ptr, Format *const format);
int CheckIfZeroDoubleString(const char *str);
char *FindFirstChar(const char *str, const char *set);
void RemoveCharacter(char *str, const char *const ptr);
void DoExtraProcessingDoubleE(char **const str_ptr, Format *const format,
                              int degree, char *suffix, int is_negative);
int IsNonNumericValue(const char *const str);
void ProcessNAN(char **const str_ptr);
