#include "test.h"

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int StrEq(const char *str1, const char *str2, int len) {
  int result = 1;
  while (len > 0 && result) {
    result = *str1++ == *str2++;
    --len;
  }
  return result;
}

START_TEST(s21_atol_test) {
  char *ar[15] = {"2423dklgjndlk14353",
                  "1234567890",
                  "1",
                  "2",
                  "-2",
                  "0",
                  "123,23456",
                  "-4536758",
                  "hjhgfdsdgfs",
                  "",
                  "-0",
                  "-1234",
                  "-",
                  "+",
                  "76543"};
  int shift = 0;
  int success = 0;
  for (int i = 0; i < 15; ++i) {
    ck_assert_int_eq(atol(ar[i]), s21_atol(ar[i], 10, &shift, 100, &success));
  }
  printf("s21_atol test passed\n");
}
END_TEST

START_TEST(s21_atold_test) {
  char *ar[15] = {"24.23e-5dklgjndlk14353",
                  "-2e-7",
                  "123.23456E12",
                  "12345.67890",
                  "1",
                  "2.",
                  "0",
                  "-45367.58e2",
                  "hjhgfdsdgfs",
                  "",
                  "-0",
                  "-123.4",
                  "-",
                  "+",
                  "76543e-1"};
  int shift = 0;
  for (int i = 0; i < 15; ++i) {
    ck_assert_int_eq(
        s21_Fabsl(atof(ar[i]) - s21_atold(ar[i], 1, &shift, 100)) < 1e-9, 1);
  }
  printf("s21_atold test passed\n");
}
END_TEST

char **InitArr(const int rows, const int cols) {
  char **arr = (char **)calloc(sizeof(char *), rows);
  for (int i = 0; i < rows; ++i) {
    arr[i] = (char *)calloc(sizeof(char), cols);
    for (int j = 0; j < cols; ++j) {
      arr[i][j] = 'a';
    }
  }
  return arr;
}

void DestroyArr(char **const arr, const int rows) {
  for (int i = 0; i < rows; ++i) {
    free(arr[i]);
  }
  free(arr);
}

START_TEST(s21_to_upper_test) {
  const char *ar[6] = {"QWERTY",
                       "",
                       "qwer,.ty",
                       "qw.)(/.ertY",
                       ";aghsGKIFASKifHASWefhskj",
                       "aEDSGFaSDFgAdfwaE"};
  const char *ar_upper[6] = {"QWERTY",
                             "",
                             "QWER,.TY",
                             "QW.)(/.ERTY",
                             ";AGHSGKIFASKIFHASWEFHSKJ",
                             "AEDSGFASDFGADFWAE"};

  for (int i = 0; i < 6; ++i) {
    char *tmp = s21_to_upper(ar[i]);
    ck_assert_int_eq(strcmp(tmp, ar_upper[i]), 0);
    free(tmp);
  }
  ck_assert_ptr_eq(s21_to_upper(NULL), NULL);
  printf("s21_to_upper test passed\n");
}
END_TEST

START_TEST(s21_to_lower_test) {
  const char *ar[6] = {"QWERTY",
                       "",
                       "qwer,.ty",
                       "qw.)(/.ertY",
                       ";aghsGKIFASKifHASWefhskj",
                       "aEDSGFaSDFgAdfwaE"};
  const char *ar_lower[6] = {"qwerty",
                             "",
                             "qwer,.ty",
                             "qw.)(/.erty",
                             ";aghsgkifaskifhaswefhskj",
                             "aedsgfasdfgadfwae"};

  for (int i = 0; i < 6; ++i) {
    char *tmp = s21_to_lower(ar[i]);
    ck_assert_int_eq(strcmp(tmp, ar_lower[i]), 0);
    free(tmp);
  }
  ck_assert_ptr_eq(s21_to_lower(NULL), NULL);
  printf("s21_to_lower test passed\n");
}
END_TEST

START_TEST(s21_insert_test) {
  char *str1 = s21_insert("GeeksForGeeks", "GFG", 0);
  char *str2 = s21_insert("GeeksForGeeks", "GFG", 1);
  char *str3 = s21_insert("GeeksForGeeks", "GFG", 2);
  char *str4 = s21_insert("GeeksForGeeks", "GFG", 3);
  char *str5 = s21_insert("GeeksForGeeks", "GFG", 4);
  char *str6 = s21_insert("GeeksForGeeks", "GFG", 5);
  char *str7 = s21_insert("GeeksForGeeks", "GFG", 6);
  char *str8 = s21_insert("GeeksForGeeks", "GFG", 7);
  char *str9 = s21_insert("GeeksForGeeks", "GFG", 8);
  char *str10 = s21_insert("GeeksForGeeks", "GFG", 9);
  char *str11 = s21_insert("GeeksForGeeks", "GFG", 10);
  char *str12 = s21_insert("GeeksForGeeks", "GFG", 11);
  char *str13 = s21_insert("GeeksForGeeks", "GFG", 12);
  char *str14 = s21_insert("GeeksForGeeks", "GFG", 13);
  char *str15 = s21_insert("", "qwerty", 0);
  char *str16 = s21_insert("qwerty", "", 0);
  char *str17 = s21_insert("qwerty", "", 128);
  ck_assert_int_eq(strcmp(str1, "GFGGeeksForGeeks"), 0);
  ck_assert_int_eq(strcmp(str2, "GGFGeeksForGeeks"), 0);
  ck_assert_int_eq(strcmp(str3, "GeGFGeksForGeeks"), 0);
  ck_assert_int_eq(strcmp(str4, "GeeGFGksForGeeks"), 0);
  ck_assert_int_eq(strcmp(str5, "GeekGFGsForGeeks"), 0);
  ck_assert_int_eq(strcmp(str6, "GeeksGFGForGeeks"), 0);
  ck_assert_int_eq(strcmp(str7, "GeeksFGFGorGeeks"), 0);
  ck_assert_int_eq(strcmp(str8, "GeeksFoGFGrGeeks"), 0);
  ck_assert_int_eq(strcmp(str9, "GeeksForGFGGeeks"), 0);
  ck_assert_int_eq(strcmp(str10, "GeeksForGGFGeeks"), 0);
  ck_assert_int_eq(strcmp(str11, "GeeksForGeGFGeks"), 0);
  ck_assert_int_eq(strcmp(str12, "GeeksForGeeGFGks"), 0);
  ck_assert_int_eq(strcmp(str13, "GeeksForGeekGFGs"), 0);
  ck_assert_int_eq(strcmp(str14, "GeeksForGeeksGFG"), 0);
  ck_assert_int_eq(strcmp(str15, "qwerty"), 0);
  ck_assert_int_eq(strcmp(str16, "qwerty"), 0);
  ck_assert_int_eq(str17 == NULL, 1);
  free(str1);
  free(str2);
  free(str3);
  free(str4);
  free(str5);
  free(str6);
  free(str7);
  free(str8);
  free(str9);
  free(str10);
  free(str11);
  free(str12);
  free(str13);
  free(str14);
  free(str15);
  free(str16);
  free(str17);
  ck_assert_ptr_eq(s21_insert(NULL, "bla bla", 0), NULL);
  ck_assert_ptr_eq(s21_insert("bla bla", NULL, 0), NULL);
  ck_assert_ptr_eq(s21_insert(NULL, NULL, 0), NULL);
  ck_assert_ptr_eq(s21_insert("bla bla", "bla _bla", 186), NULL);
  printf("s21_insert test passed\n");
}
END_TEST

START_TEST(s21_trim_test) {
  char *str1 = NULL;
  str1 = s21_trim("  \t      GeeksForG\teeks \t         ", " \t Gs");
  ck_assert_int_eq(strcmp("eeksForG\teek", str1), 0);
  free(str1);

  str1 = s21_trim("  \t      GeeksForG\teeks \t         ", "");
  ck_assert_int_eq(strcmp("GeeksForG\teeks", str1), 0);
  free(str1);

  str1 = s21_trim("  \t      GeeksForG\teeks \t         ", " \t GeksFor");
  ck_assert_int_eq(strcmp("", str1), 0);
  free(str1);

  str1 = s21_trim("  \t      GeeksForG\teeks \t         ", " \t Geks");
  ck_assert_int_eq(strcmp("For", str1), 0);
  free(str1);

  str1 = s21_trim("  \t      GeeksForG\teeks \t         ", " \t Geksor");
  ck_assert_int_eq(strcmp("F", str1), 0);
  free(str1);

  str1 = s21_trim("  \t      GeeksForG\teeks \t         ", "For");
  ck_assert_int_eq(strcmp("  \t      GeeksForG\teeks \t         ", str1), 0);
  free(str1);

  str1 = s21_trim("", "For");
  ck_assert_int_eq(strcmp("", str1), 0);
  free(str1);

  ck_assert_ptr_eq(s21_trim(NULL, "bla bla"), NULL);
  ck_assert_ptr_eq(s21_trim("bla bla", NULL), NULL);
  ck_assert_ptr_eq(s21_trim(NULL, NULL), NULL);
  printf("s21_trim test passed\n");
}
END_TEST

START_TEST(s21_sscanf_test) {
  char *str =
      "-12.324e-21 -123.67654e222            65qwerty    %           f -036540 "
      "% "
      "-0xfffff  "
      " "
      " g "
      "-0xaaaAff -294967294QWERTY QWERTY12345 12345 sdkfg dfgxsljflsdkfj "
      "-0X12344ABCDEF 0x123bcdeF -0x123 0XABC-01234562 07654321123 "
      "01233123 013 014356435 0xBCa 123123 -.123123e13 23456789 "
      "     -519.213234234e80 0x01310bc5b91922 -13slfj456";

  int act_mine = 0, act_sys = 0;
  char **mine = InitArr(TEST_AR_SIZE, TEST_STR_SIZE);
  char **sys = InitArr(TEST_AR_SIZE, TEST_STR_SIZE);

  /* #if defined(__linux__) */
  /*   printf("s21_sscanf null test\n"); */
  /*   act_sys = sscanf( */
  /*       str, NULL, (float *)sys[29], (double *)sys[0], (wchar_t *)sys[1], */
  /*       (int *)sys[2], (unsigned int *)sys[3], (unsigned int *)sys[4], */
  /*       (int *)sys[5], (int *)sys[6], (char *)sys[7], (long *)sys[8], */
  /*       (short *)sys[9], (int *)sys[10], (wchar_t *)sys[11], (long *)sys[12],
   */
  /*       (long *)sys[13], (short *)sys[14], (short *)sys[15], (long *)sys[16],
   */
  /*       (long *)sys[17], (short *)sys[18], (short *)sys[19], (long *)sys[20],
   */
  /*       (short *)sys[21], (long unsigned int *)sys[22], (float *)sys[24], */
  /*       (long double *)(sys[25]), (void **)(sys[26]), (short int *)sys[27],
   */
  /*       (int *)sys[28]); */
  /*   act_mine = */
  /*       s21_sscanf(str, NULL, mine[29], mine[0], mine[1], mine[2], mine[3],
   */
  /*                  mine[4], mine[5], mine[6], mine[7], mine[8], mine[9],
   * mine[10], */
  /*                  mine[11], mine[12], mine[13], mine[14], mine[15],
   * mine[16], */
  /*                  mine[17], mine[18], mine[19], mine[20], mine[21],
   * mine[22], */
  /*                  mine[24], mine[25], mine[26], mine[27], mine[28]); */
  /*   ck_assert_int_eq(act_mine, act_sys); */
  /*   for (int i = 0; i < TEST_AR_SIZE; ++i) { */
  /*     ck_assert_int_eq(StrEq(mine[i], sys[i], TEST_STR_SIZE), 1); */
  /*   } */
  /*   ck_assert_int_eq(act_mine, act_sys); */
  /*   DestroyArr(mine, TEST_AR_SIZE); */
  /*   DestroyArr(sys, TEST_AR_SIZE); */
  /* #endif */

  /* act_mine = 0, act_sys = 0; */
  /* mine = InitArr(TEST_AR_SIZE, TEST_STR_SIZE); */
  /* sys = InitArr(TEST_AR_SIZE, TEST_STR_SIZE); */

  act_mine =
      s21_sscanf(str, FORMAT, mine[29], mine[0], mine[1], mine[2], mine[3],
                 mine[4], mine[5], mine[6], mine[7], mine[8], mine[9], mine[10],
                 mine[11], mine[12], mine[13], mine[14], mine[15], mine[16],
                 mine[17], mine[18], mine[19], mine[20], mine[21], mine[22],
                 mine[24], mine[25], mine[26], mine[27], mine[28]);

  act_sys = sscanf(
      str, FORMAT, (float *)sys[29], (double *)sys[0], (wchar_t *)sys[1],
      (int *)sys[2], (unsigned int *)sys[3], (unsigned int *)sys[4],
      (int *)sys[5], (int *)sys[6], (char *)sys[7], (long *)sys[8],
      (short *)sys[9], (int *)sys[10], (wchar_t *)sys[11], (long *)sys[12],
      (long *)sys[13], (short *)sys[14], (short *)sys[15], (long *)sys[16],
      (long *)sys[17], (short *)sys[18], (short *)sys[19], (long *)sys[20],
      (short *)sys[21], (long unsigned int *)sys[22], (float *)sys[24],
      (long double *)(sys[25]), (void **)(sys[26]), (short int *)sys[27],
      (int *)sys[28]);

  for (int i = 1; i < TEST_AR_SIZE; ++i) {
    if (i != 25) {
      ck_assert_int_eq(StrEq(mine[i], sys[i], TEST_STR_SIZE), 1);
    }
  }
  ck_assert_int_eq(act_mine, act_sys);

  DestroyArr(mine, TEST_AR_SIZE);
  DestroyArr(sys, TEST_AR_SIZE);
  printf("s21_sscanf test passed\n");
}
END_TEST

START_TEST(s21_sprintf_test) {
  int act_mine = 0, act_sys = 0;
  int written_mine = 0, written_sys = 0;
  int int_val0 = 0, int_val1 = 12342567, int_val2 = -12342567;
  long long_val0 = 0, long_val1 = 123425768905678967,
       long_val2 = -1265734256163789176;
  short short_val0 = 0, short_val1 = 122, short_val2 = -234;
  long double val_long_double = 93456789.9955666666435673456783245678435678e-3L;
  long double val_long_double1 = 63.9955666666435673456783245678435678e-15L;
  long double val_long_double2 = -43.8e15L;
  long double val_long_double3 = 0.0L;
  /* long double val_long_double4 = 1.0L / 0.0L; */
  /* long double val_long_double5 = -val_long_double4; */
  /* long double val_long_double6 = sqrt(-5.0L); */
  /* long double val_long_double7 = -sqrt(-5.0L); */

  double val_double = 93456789.9955666666435673456783245678435678e-3;
  double val_double1 = 63.9955666666435673456783245678435678e-15;
  double val_double2 = -43.8e15;
  double val_double3 = 0.0;
  /* double val_double4 = 1.0 / 0.0; */
  /* double val_double5 = -val_double4; */
  /* double val_double6 = sqrt(-5.0); */
  /* double val_double7 = -sqrt(-5.0); */

  char c0 = 'g', c1 = 'D', c2 = 't';
  char *str0 =
      "sfjlfwefghelsfdsdfsdfsdf  sfsfsdfsdf  sdfsdfsdfsdfsd  "
      "sdfsdfsdfsdfqw';;lada;ll";
  char *str1 = "";
  char *str2 = "ASFASDGadsgfkdfajgldfkjgsafskldjfSADFSDF";

  /* #if defined(__linux__) */
  /*   wchar_t *w_str0 = L"🍌zß水🍌sdf"; */
  /*   wchar_t w_c0 = L'🍌'; */
  /*   wchar_t w_c1 = L'ß'; */
  /*   wchar_t w_c2 = L'水'; */
  /* #endif */

  char *buffer_mine = calloc(TEST_STR_SIZE * 50, 1);
  char *buffer_sys = calloc(TEST_STR_SIZE * 50, 1);

  char *cursor_mine = buffer_mine;
  char *cursor_sys = buffer_sys;

  /* #if defined(__linux__) */
  /*   printf("s21_sprintf null test\n"); */
  /*   act_sys = sprintf(cursor_sys, NULL, 30, 12, int_val0, int_val0, int_val0,
   */
  /**/
  /*                     int_val0, int_val0, 15, int_val1, int_val1, int_val1,
   */
  /*                     int_val1, int_val1, 10, int_val2, int_val2, int_val2,
   */
  /*                     int_val2, &written_sys, int_val2, &int_val2, 99999); */
  /*   act_mine = */
  /*       s21_sprintf(cursor_mine, NULL, 30, 12, int_val0, int_val0, int_val0,
   */
  /*                   int_val0, int_val0, 15, int_val1, int_val1, int_val1, */
  /*                   int_val1, int_val1, 10, int_val2, int_val2, int_val2, */
  /*                   int_val2, &written_mine, int_val2, &int_val2, 99999); */
  /*   ck_assert_int_eq(act_sys, act_mine); */
  /* #endif */

  act_sys =
      sprintf(cursor_sys, FORMATD_SPRINTF, 30, 12, int_val0, int_val0, int_val0,
              int_val0, int_val0, 15, int_val1, int_val1, int_val1, int_val1,
              int_val1, 10, int_val2, int_val2, int_val2, int_val2,
              &written_sys, int_val2, &int_val2, 99999);
  act_mine = s21_sprintf(cursor_mine, FORMATD_SPRINTF, 30, 12, int_val0,
                         int_val0, int_val0, int_val0, int_val0, 15, int_val1,
                         int_val1, int_val1, int_val1, int_val1, 10, int_val2,
                         int_val2, int_val2, int_val2, &written_mine, int_val2,
                         &int_val2, 99999);
  ck_assert_int_eq(strcmp(buffer_mine, buffer_sys), 0);
  ck_assert_int_eq(act_mine, act_sys);
  ck_assert_int_eq(written_mine, written_sys);
  cursor_sys += act_sys;
  cursor_mine += act_mine;

  act_sys = sprintf(cursor_sys, FORMATHD_SPRINTF, 10, short_val0, short_val0,
                    short_val0, short_val0, short_val0, 15, short_val1,
                    short_val1, short_val1, short_val1, short_val1, 10,
                    short_val2, short_val2, short_val2, short_val2, short_val2);
  act_mine =
      s21_sprintf(cursor_mine, FORMATHD_SPRINTF, 10, short_val0, short_val0,
                  short_val0, short_val0, short_val0, 15, short_val1,
                  short_val1, short_val1, short_val1, short_val1, 10,
                  short_val2, short_val2, short_val2, short_val2, short_val2);
  ck_assert_int_eq(strcmp(buffer_mine, buffer_sys), 0);
  ck_assert_int_eq(act_mine, act_sys);
  cursor_sys += act_sys;
  cursor_mine += act_mine;

  act_sys = sprintf(cursor_sys, FORMATLD_SPRINTF, 10, long_val0, long_val0,
                    long_val0, long_val0, long_val0, 15, long_val1, long_val1,
                    long_val1, long_val1, long_val1, 10, long_val2, long_val2,
                    long_val2, long_val2, long_val2);
  act_mine = s21_sprintf(
      cursor_mine, FORMATLD_SPRINTF, 10, long_val0, long_val0, long_val0,
      long_val0, long_val0, 15, long_val1, long_val1, long_val1, long_val1,
      long_val1, 10, long_val2, long_val2, long_val2, long_val2, long_val2);
  ck_assert_int_eq(strcmp(buffer_mine, buffer_sys), 0);
  ck_assert_int_eq(act_mine, act_sys);
  cursor_sys += act_sys;
  cursor_mine += act_mine;

  act_sys = sprintf(cursor_sys, FORMATLI_SPRINTF, 10, long_val0, long_val0,
                    long_val0, long_val0, long_val0, 15, long_val1, long_val1,
                    long_val1, long_val1, long_val1, 10, long_val2, long_val2,
                    long_val2, long_val2, long_val2);
  act_mine = s21_sprintf(
      cursor_mine, FORMATLI_SPRINTF, 10, long_val0, long_val0, long_val0,
      long_val0, long_val0, 15, long_val1, long_val1, long_val1, long_val1,
      long_val1, 10, long_val2, long_val2, long_val2, long_val2, long_val2);
  ck_assert_int_eq(strcmp(buffer_mine, buffer_sys), 0);
  ck_assert_int_eq(act_mine, act_sys);
  cursor_sys += act_sys;
  cursor_mine += act_mine;

  act_sys = sprintf(cursor_sys, FORMATLU_SPRINTF, 10, long_val0, long_val0,
                    long_val0, long_val0, long_val0, 15, long_val1, long_val1,
                    long_val1, long_val1, long_val1, 10, long_val2, long_val2,
                    long_val2, long_val2, long_val2);
  act_mine = s21_sprintf(
      cursor_mine, FORMATLU_SPRINTF, 10, long_val0, long_val0, long_val0,
      long_val0, long_val0, 15, long_val1, long_val1, long_val1, long_val1,
      long_val1, 10, long_val2, long_val2, long_val2, long_val2, long_val2);
  ck_assert_int_eq(strcmp(buffer_mine, buffer_sys), 0);
  ck_assert_int_eq(act_mine, act_sys);
  cursor_sys += act_sys;
  cursor_mine += act_mine;

  act_sys = sprintf(cursor_sys, FORMATLX_SPRINTF, 10, long_val0, long_val0,
                    long_val0, long_val0, long_val0, 15, long_val1, long_val1,
                    long_val1, long_val1, long_val1, 10, long_val2, long_val2,
                    long_val2, long_val2, long_val2);
  act_mine = s21_sprintf(
      cursor_mine, FORMATLX_SPRINTF, 10, long_val0, long_val0, long_val0,
      long_val0, long_val0, 15, long_val1, long_val1, long_val1, long_val1,
      long_val1, 10, long_val2, long_val2, long_val2, long_val2, long_val2);
  ck_assert_int_eq(strcmp(buffer_mine, buffer_sys), 0);
  ck_assert_int_eq(act_mine, act_sys);
  cursor_sys += act_sys;
  cursor_mine += act_mine;

  act_sys = sprintf(cursor_sys, FORMATLO_SPRINTF, 10, long_val0, long_val0,
                    long_val0, long_val0, long_val0, 15, long_val1, long_val1,
                    long_val1, long_val1, long_val1, 60, long_val2, long_val2,
                    long_val2, long_val2, long_val2);
  act_mine = s21_sprintf(
      cursor_mine, FORMATLO_SPRINTF, 10, long_val0, long_val0, long_val0,
      long_val0, long_val0, 15, long_val1, long_val1, long_val1, long_val1,
      long_val1, 60, long_val2, long_val2, long_val2, long_val2, long_val2);
  ck_assert_int_eq(strcmp(buffer_mine, buffer_sys), 0);
  ck_assert_int_eq(act_mine, act_sys);
  cursor_sys += act_sys;
  cursor_mine += act_mine;

#if defined(__linux__)
  setlocale(LC_ALL, "en_US.utf8");
  act_sys = sprintf(cursor_sys, FORMATS_SPRINTF, ARGLIST_S);
  act_mine = s21_sprintf(cursor_mine, FORMATS_SPRINTF, ARGLIST_S);
  /* printf("Linux sprintf test\n"); */
  /* printf("%s\n%s\n", cursor_sys, cursor_mine); */
  ck_assert_int_eq(strcmp(buffer_mine, buffer_sys), 0);
  ck_assert_int_eq(act_mine, act_sys);
  cursor_sys += act_sys;
  cursor_mine += act_mine;
#endif

#if defined(__APPLE__)
  act_sys = sprintf(cursor_sys, FORMATS_SPRINTF, ARGLIST_S);
  act_mine = s21_sprintf(cursor_mine, FORMATS_SPRINTF, ARGLIST_S);
  printf("Apple sprintf test\n");
  ck_assert_int_eq(strcmp(buffer_mine, buffer_sys), 0);
  ck_assert_int_eq(act_mine, act_sys);
  cursor_sys += act_sys;
  cursor_mine += act_mine;
#endif

#if defined(__linux__)
  setlocale(LC_ALL, "en_US.utf8");
  act_sys = sprintf(cursor_sys, FORMATC_SPRINTF, ARGLIST_C);
  act_mine = s21_sprintf(cursor_mine, FORMATC_SPRINTF, ARGLIST_C);
  printf("Linux sprintf test\n");
#endif

#if defined(__APPLE__)
  act_sys = sprintf(cursor_sys, FORMATC_SPRINTF, ARGLIST_C);
  act_mine = s21_sprintf(cursor_mine, FORMATC_SPRINTF, ARGLIST_C);
  printf("Apple sprintf test\n");
#endif

  ck_assert_int_eq(strcmp(buffer_mine, buffer_sys), 0);
  ck_assert_int_eq(act_mine, act_sys);
  cursor_sys += act_sys;
  cursor_mine += act_mine;

  char str[10000] = {0};
  char strx1[10000] = {0};
  char str_1[10000] = {0};
  char str1_1[10000] = {0};
  char str_2[10000] = {0};
  char str1_2[10000] = {0};
  char str_3[10000] = {0};
  char str1_3[10000] = {0};
  /* char str_4[10000] = {0}; */
  /* char str1_4[10000] = {0}; */

  act_sys = sprintf(str, FORMAT_LONG_DOUBLE, ARG_LIST_LONG_DOUBLE);
  act_mine = s21_sprintf(strx1, FORMAT_LONG_DOUBLE, ARG_LIST_LONG_DOUBLE);
  ck_assert_int_eq(act_mine, act_sys);
  act_sys = sprintf(str_1, FORMAT_LONG_DOUBLE, ARG_LIST_LONG_DOUBLE1);
  act_mine = s21_sprintf(str1_1, FORMAT_LONG_DOUBLE, ARG_LIST_LONG_DOUBLE1);

  ck_assert_int_eq(act_mine, act_sys);
  act_sys = sprintf(str_2, FORMAT_LONG_DOUBLE, ARG_LIST_LONG_DOUBLE2);
  act_mine = s21_sprintf(str1_2, FORMAT_LONG_DOUBLE, ARG_LIST_LONG_DOUBLE2);

  ck_assert_int_eq(act_mine, act_sys);
  act_sys = sprintf(str_3, FORMAT_LONG_DOUBLE, ARG_LIST_LONG_DOUBLE3);
  act_mine = s21_sprintf(str1_3, FORMAT_LONG_DOUBLE, ARG_LIST_LONG_DOUBLE3);

  ck_assert_int_eq(act_mine, act_sys);
  /* act_sys = sprintf(str_4, FORMAT_LONG_DOUBLE, ARG_LIST_LONG_DOUBLE4); */
  /* act_mine = s21_sprintf(str1_4, FORMAT_LONG_DOUBLE, ARG_LIST_LONG_DOUBLE4);
   */

  /* ck_assert_int_eq(act_mine, act_sys); */
  ck_assert_int_eq(s21_strcmp(strx1, str), 0);
  ck_assert_int_eq(s21_strcmp(str1_1, str_1), 0);
  ck_assert_int_eq(s21_strcmp(str1_2, str_2), 0);
  ck_assert_int_eq(s21_strcmp(str1_3, str_3), 0);
  /* ck_assert_int_eq(s21_strcmp(str1_4, str_4), 0); */

  act_sys = sprintf(str, FORMAT_DOUBLE, ARG_LIST_DOUBLE);
  act_mine = s21_sprintf(strx1, FORMAT_DOUBLE, ARG_LIST_DOUBLE);
  ck_assert_int_eq(act_mine, act_sys);
  act_sys = sprintf(str_1, FORMAT_DOUBLE, ARG_LIST_DOUBLE1);
  act_mine = s21_sprintf(str1_1, FORMAT_DOUBLE, ARG_LIST_DOUBLE1);
  ck_assert_int_eq(act_mine, act_sys);
  act_sys = sprintf(str_2, FORMAT_DOUBLE, ARG_LIST_DOUBLE2);
  act_mine = s21_sprintf(str1_2, FORMAT_DOUBLE, ARG_LIST_DOUBLE2);
  ck_assert_int_eq(act_mine, act_sys);
  act_sys = sprintf(str_3, FORMAT_DOUBLE, ARG_LIST_DOUBLE3);
  act_mine = s21_sprintf(str1_3, FORMAT_DOUBLE, ARG_LIST_DOUBLE3);
  ck_assert_int_eq(act_mine, act_sys);
  /* act_sys = sprintf(str_4, FORMAT_DOUBLE, ARG_LIST_DOUBLE4); */
  /* act_mine = s21_sprintf(str1_4, FORMAT_DOUBLE, ARG_LIST_DOUBLE4); */
  /* ck_assert_int_eq(act_mine, act_sys); */
  ck_assert_int_eq(s21_strcmp(strx1, str), 0);
  ck_assert_int_eq(s21_strcmp(str1_1, str_1), 0);
  ck_assert_int_eq(s21_strcmp(str1_2, str_2), 0);
  ck_assert_int_eq(s21_strcmp(str1_3, str_3), 0);
  /* ck_assert_int_eq(s21_strcmp(str1_4, str_4), 0); */

  free(buffer_mine);
  free(buffer_sys);
  printf("s21_sprintf test passed\n");
}
END_TEST

START_TEST(s21_memcmp_test) {
  char array1[] = "Hello World!";
  char array2[] = "Hello World!";

  ck_assert_int_eq(memcmp(array1, array2, sizeof(array1)) > 0,
                   s21_memcmp(array1, array2, sizeof(array1)) > 0);

  array2[0] = 'X';

  ck_assert_int_eq(memcmp(array1, array2, sizeof(array1)) > 0,
                   s21_memcmp(array1, array2, sizeof(array1)) > 0);

  array2[0] = 'H';

  ck_assert_int_eq(memcmp(array1, array2, sizeof(array1) / 2) > 0,
                   s21_memcmp(array1, array2, sizeof(array1) / 2) > 0);
  ck_assert_int_eq(memcmp("", "", 0), s21_memcmp("", "", 0));

  ck_assert_int_eq(memcmp("", "sjfsjdf", 0) > 0,
                   s21_memcmp("", "sjfsjdf", 0) > 0);
  ck_assert_int_eq(memcmp("qwe", "", 0) > 0, s21_memcmp("qwe", "", 0) > 0);
  printf("s21_memcmp test passed\n");
}
END_TEST

START_TEST(s21_memcpy_test) {
  char source[] = "Hello World!";
  char destination[sizeof(source)];
  memcpy(destination, source, sizeof(source));
  ck_assert_str_eq(destination,
                   s21_memcpy(destination, source, sizeof(source)));
  strcpy(source, "Goodbye!");
  ck_assert_str_eq(destination,
                   s21_memcpy(destination, source, sizeof(source)));
  printf("s21_memcpy test passed\n");
}
END_TEST

START_TEST(s21_memset_test) {
  char array[20] = {'\0'};
  char array1[20] = {'\0'};
  memset(array, 'A', sizeof(array) - 1);
  ck_assert_str_eq(array, s21_memset(array1, 'A', sizeof(array1) - 1));
  memset(array, 'B', sizeof(array) / 2);
  ck_assert_str_eq(array, s21_memset(array1, 'B', sizeof(array1) / 2));
  printf("s21_memset test passed\n");
}
END_TEST

START_TEST(test_memchr_found_middle) {
  const char str[] = "hello, world!";
  char *result = s21_memchr(str, 'o', strlen(str));
  ck_assert_ptr_nonnull(result);
  ck_assert_int_eq(*result, 'o');
  ck_assert_str_eq(result, "o, world!");
  printf("s21_smemchr_found_middle test passed\n");
}
END_TEST

START_TEST(test_memchr_not_found) {
  const char str[] = "hello, world!";
  char *result = s21_memchr(str, 'z', strlen(str));
  ck_assert_ptr_null(result);
  printf("s21_memchr_not_found test passed\n");
}
END_TEST

START_TEST(test_memchr_found_start) {
  const char str[] = "hello, world!";
  char *result = s21_memchr(str, 'h', strlen(str));
  ck_assert_ptr_nonnull(result);
  ck_assert_int_eq(*result, 'h');
  ck_assert_str_eq(result, "hello, world!");
  printf("s21_memchr_found_start test passed\n");
}
END_TEST

START_TEST(test_memchr_empty_string) {
  const char str[] = "";
  char *result = s21_memchr(str, 'h', strlen(str));
  ck_assert_ptr_null(result);
  printf("s21_memchr_empty_string test passed\n");
}
END_TEST

START_TEST(test_memchr_with_limit) {
  const char str[] = "hello, world!";
  char *result = s21_memchr(str, 'w', 5);
  ck_assert_ptr_null(result);
  printf("s21_memchr_with_limit test passed\n");
}
END_TEST

START_TEST(s21_strlen_test) {
  const char *str1 = "Hello";
  const char *str2 = "";
  const char *str3 = "sjafhsa;fksl;fjlskdjf";

  ck_assert_int_eq(strlen(str1), s21_strlen(str1));
  ck_assert_int_eq(strlen(str2), s21_strlen(str2));
  ck_assert_int_eq(strlen(str3), s21_strlen(str3));

  printf("s21_strlen test passed\n");
}
END_TEST

START_TEST(is_delimiter_test) {
  const char *delim = " ,.!?";

  ck_assert_int_eq(is_delimiter(' ', delim), 1);
  ck_assert_int_eq(is_delimiter(',', delim), 1);
  ck_assert_int_eq(is_delimiter('!', delim), 1);
  ck_assert_int_eq(is_delimiter('a', delim), 0);
  printf("is_delimiter test passed\n");
}
END_TEST

START_TEST(s21_strchr_test) {
  const char *str = "Hello, world!";

  ck_assert_ptr_eq(s21_strchr(str, 'H'), str);
  ck_assert_ptr_eq(s21_strchr(str, 'o'), str + 4);
  ck_assert_ptr_eq(s21_strchr(str, '!'), str + 12);
  ck_assert_ptr_eq(s21_strchr(str, 'z'), NULL);
  printf("s21_strchr test passed\n");
}
END_TEST

START_TEST(s21_strrchr_test) {
  const char *str = "Hello, world!";

  ck_assert_ptr_eq(s21_strrchr(str, 'o'), str + 8);
  ck_assert_ptr_eq(s21_strrchr(str, 'H'), str);
  printf("s21_strrchr test passed\n");
}
END_TEST

START_TEST(s21_strstr_test) {
  const char *haystack = "Hello, world!";

  ck_assert_ptr_eq(s21_strstr(haystack, "world"), haystack + 7);
  printf("s21_strstr test passed\n");
}
END_TEST

START_TEST(s21_strpbrk_test) {
  const char *str1 = "abcdef";

  ck_assert_ptr_eq(s21_strpbrk(str1, "cde"), str1 + 2);
  printf("s21_strbrk test passed\n");
}
END_TEST

START_TEST(s21_strtok_test) {
  char str[] = "Hello, world! This is a test.";
  char *delim = " ,.!";
  char *token;

  token = s21_strtok(str, delim);
  ck_assert_str_eq(token, "Hello");

  token = s21_strtok(NULL, delim);
  ck_assert_str_eq(token, "world");
  printf("s21_strtok test passed\n");
}
END_TEST

START_TEST(s21_strcspn_test) {
  const char *str1_arr[10] = {"hello world",
                              "abcdefg",
                              "",
                              "1234567890",
                              "The quick brown fox",
                              "sample text",
                              "another example",
                              "teststring",
                              "foobar",
                              "s21_string"};

  const char *str2_arr[10] = {"xyz", "bdf",   "abc", "0",   "fox",
                              "tex", "ample", "xyz", "bar", "str"};

  size_t expected_results[10] = {strcspn("hello world", "xyz"),
                                 strcspn("abcdefg", "bdf"),
                                 strcspn("", "abc"),
                                 strcspn("1234567890", "0"),
                                 strcspn("The quick brown fox", "fox"),
                                 strcspn("sample text", "tex"),
                                 strcspn("another example", "ample"),
                                 strcspn("teststring", "xyz"),
                                 strcspn("foobar", "bar"),
                                 strcspn("s21_string", "str")};

  for (int i = 0; i < 10; ++i) {
    size_t result = s21_strcspn(str1_arr[i], str2_arr[i]);
    ck_assert_uint_eq(result, expected_results[i]);
  }

  ck_assert_uint_eq(s21_strcspn("hello", ""), 5);
  ck_assert_uint_eq(s21_strcspn("", "abc"), 0);
  ck_assert_uint_eq(s21_strcspn("hello", "h"), 0);
  ck_assert_uint_eq(s21_strcspn("hello", "o"), 4);
  ck_assert_uint_eq(s21_strcspn("aaaaa", "a"), 0);
  ck_assert_uint_eq(s21_strcspn("abcde", "xyz"), 5);

  printf("s21_strcspn test passed\n");
}
END_TEST

START_TEST(s21_strerror_test) {
#if defined(__APPLE__)
#define TEST_MAX 106
#define TEST_MIN 0
#elif defined(__linux__)
#define TEST_MAX 133
#define TEST_MIN 0
#else
#error "Unsupported platform"
#endif

  int test_error_numbers[] = {
      TEST_MIN,     1,  2,   22, TEST_MAX - 1, TEST_MAX,
      TEST_MAX + 1, -1, 999, 50, 75,           100,
  };

  int num_tests = sizeof(test_error_numbers) / sizeof(test_error_numbers[0]);

  for (int i = 0; i < num_tests; ++i) {
    int error_num = test_error_numbers[i];
    char *expected = strerror(error_num);
    char *actual = s21_strerror(error_num);

    if (error_num >= TEST_MIN && error_num <= TEST_MAX) {
      ck_assert_str_eq(actual, expected);
    } else {
      char expected_unknown[1000];
#if defined(__APPLE__)
      s21_sprintf(expected_unknown, "Unknown error: %d", error_num);
#elif defined(__linux__)
      s21_sprintf(expected_unknown, "Unknown error %d", error_num);
#endif
      ck_assert_str_eq(actual, expected_unknown);
    }
  }

  ck_assert_str_eq(s21_strerror(0), strerror(0));

  ck_assert_str_eq(s21_strerror(TEST_MAX), strerror(TEST_MAX));

#if defined(__APPLE__)
  char expected_unknown_neg[1000];
  s21_sprintf(expected_unknown_neg, "Unknown error: %d", -1);
  ck_assert_str_eq(s21_strerror(-1), expected_unknown_neg);
#elif defined(__linux__)
  char expected_unknown_neg[1000];
  s21_sprintf(expected_unknown_neg, "Unknown error %d", -1);
  ck_assert_str_eq(s21_strerror(-1), expected_unknown_neg);
#endif

  printf("s21_strerror test passed\n");
}
END_TEST

START_TEST(s21_strncat_test) {
  const char *dest_arr[10] = {
      "Hello",  "",     "Start",         "Concatenate",           "12345",
      "OpenAI", "Test", "C programming", "LongStringDestination", "EdgeCase"};

  const char *src_arr[10] = {" World",
                             "Non-empty",
                             "",
                             " Function",
                             "67890",
                             "",
                             " Case",
                             " with multiple words",
                             " and more content",
                             ""};

  s21_size_t n_arr[10] = {6, 5, 0, 9, 3, 10, 4, 20, 15, 0};

  char expected_dest[10][100];
  char actual_dest[10][100];

  for (int i = 0; i < 10; ++i) {
    memset(expected_dest[i], 0, sizeof(expected_dest[i]));
    memset(actual_dest[i], 0, sizeof(actual_dest[i]));

    strncpy(expected_dest[i], dest_arr[i], sizeof(expected_dest[i]) - 1);
    strncpy(actual_dest[i], dest_arr[i], sizeof(actual_dest[i]) - 1);

    strncat(expected_dest[i], src_arr[i], n_arr[i]);

    s21_strncat(actual_dest[i], src_arr[i], n_arr[i]);

    ck_assert_str_eq(actual_dest[i], expected_dest[i]);
  }

  char dest1[50] = "No change";
  char dest2[50] = "No change";
  s21_strncat(dest1, "Should not append", 0);
  strncat(dest2, "Should not append", 0);
  ck_assert_str_eq(dest1, dest2);

  char dest3[50] = "Short ";
  char dest4[50] = "Short ";
  s21_strncat(dest3, "append", 10);
  strncat(dest4, "append", 10);
  ck_assert_str_eq(dest3, dest4);

  char dest5[50] = "Existing";
  char dest6[50] = "Existing";
  s21_strncat(dest5, "", 5);
  strncat(dest6, "", 5);
  ck_assert_str_eq(dest5, dest6);

  char dest7[50] = "";
  char dest8[50] = "";
  s21_strncat(dest7, "Add to empty", 13);
  strncat(dest8, "Add to empty", 13);
  ck_assert_str_eq(dest7, dest8);

  char dest9[50] = "Exact ";
  char dest10[50] = "Exact ";
  s21_strncat(dest9, "Match", 6);
  strncat(dest10, "Match", 6);
  ck_assert_str_eq(dest9, dest10);

  printf("s21_strncat test passed\n");
}
END_TEST

START_TEST(s21_strncmp_test) {
  const char *str1_arr[15] = {
      "hello",         "hello",      "abcdef",        "abcdef",
      "abc",           "",           "test",          "",
      "Hello, World!", "1234567890", "CaseSensitive", "unicode_",
      "abc\0def",      "abc",        "abcde"};

  const char *str2_arr[15] = {
      "hello",         "hella",    "abcxyz", "abcdef\0xyz",   "abcdef",
      "nonempty",      "",         "",       "Hello, World!", "12345",
      "casesensitive", "unicode_", "abcxyz", "abc",           "abcde"};

  size_t n_arr[15] = {5, 5, 3, 10, 6, 5, 5, 5, 13, 10, 12, 12, 6, 3, 5};

  int num_tests = 15;

  for (int i = 0; i < num_tests; ++i) {
    int expected = strncmp(str1_arr[i], str2_arr[i], n_arr[i]);
    int actual = s21_strncmp(str1_arr[i], str2_arr[i], n_arr[i]);

    if (expected < 0) {
      ck_assert_int_lt(actual, 0);
    } else if (expected > 0) {
      ck_assert_int_gt(actual, 0);
    } else {
      ck_assert_int_eq(actual, 0);
    }
  }

  ck_assert_int_eq(s21_strncmp("any string", "another string", 0), 0);
  ck_assert_int_eq(s21_strncmp("", "", 0), 0);
  ck_assert_int_eq(s21_strncmp("a", "", 0), 0);
  ck_assert_int_eq(s21_strncmp("", "a", 0), 0);

  ck_assert_int_eq(s21_strncmp("short", "short", 100), 0);
  ck_assert_int_lt(s21_strncmp("short", "shorta", 100), 0);
  ck_assert_int_gt(s21_strncmp("shorta", "short", 100), 0);

  printf("s21_strncmp test passed\n");
}
END_TEST

START_TEST(s21_strncpy_test) {
  const char *dest_arr[10] = {"Hello, World!", "",
                              "Short",         "Destination",
                              "AnotherTest",   "ExistingData",
                              "BoundaryCase",  "12345",
                              "TestString",    "FillWithData"};

  const char *src_arr[10] = {"Goodbye!",     "Non-empty", "",    "DataToCopy",
                             "ExtraData",    "CopyHere",  "End", "67890",
                             "CompleteCopy", "AddZeros"};

  size_t n_arr[10] = {9, 5, 10, 20, 5, 8, 3, 5, 12, 10};

  int num_tests = 10;

  for (int i = 0; i < num_tests; ++i) {
    char expected_dest[100];
    char actual_dest[100];

    memset(expected_dest, 'X', sizeof(expected_dest));
    memset(actual_dest, 'X', sizeof(actual_dest));

    strncpy(expected_dest, dest_arr[i], sizeof(expected_dest) - 1);
    strncpy(actual_dest, dest_arr[i], sizeof(actual_dest) - 1);

    strncpy(expected_dest, src_arr[i], n_arr[i]);

    s21_strncpy(actual_dest, src_arr[i], n_arr[i]);

    ck_assert_mem_eq(actual_dest, expected_dest, n_arr[i] + 1);
  }

  /* char dest1[50] = "OriginalData"; */
  /* char dest2[50] = "OriginalData"; */
  /* s21_strncpy(dest1, "ShouldNotCopy", 0); */
  /* strncpy(dest2, "ShouldNotCopy", 0); */
  /* ck_assert_mem_eq(dest1, dest2, strlen(dest2)); */
  /* ck_assert_str_eq(dest1, dest2); */

  char dest3[50] = "Short";
  char dest4[50] = "Short";
  s21_strncpy(dest3, "Hi", 5);
  strncpy(dest4, "Hi", 5);
  ck_assert_mem_eq(dest3, dest4, 5 + 1);
  ck_assert_str_eq(dest3, dest4);

  char dest5[50] = "ExistingData";
  char dest6[50] = "ExistingData";
  s21_strncpy(dest5, "", 5);
  strncpy(dest6, "", 5);
  ck_assert_mem_eq(dest5, dest6, 5);
  for (size_t i = 0; i < 5; ++i) {
    ck_assert_int_eq(dest5[i], '\0');
    ck_assert_int_eq(dest6[i], '\0');
  }

  char dest7[50] = "";
  char dest8[50] = "";
  s21_strncpy(dest7, "AddData", 8);
  strncpy(dest8, "AddData", 8);
  ck_assert_mem_eq(dest7, dest8, 7 + 1);
  ck_assert_str_eq(dest7, dest8);

  char dest9[50] = "ExactLen";
  char dest10[50] = "ExactLen";
  s21_strncpy(dest9, "Match", 6);
  strncpy(dest10, "Match", 6);
  ck_assert_mem_eq(dest9, dest10, 5 + 1);
  ck_assert_str_eq(dest9, dest10);

  char dest11[50] = "TestData";
  char dest12[50] = "TestData";
  s21_strncpy(dest11, "Hi", 10);
  strncpy(dest12, "Hi", 10);
  ck_assert_mem_eq(dest11, dest12, 10 + 1);
  ck_assert_str_eq(dest11, dest12);

  printf("s21_strncpy test passed\n");
}
END_TEST

Suite *s21_test_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_test_suite");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, s21_strerror_test);
  tcase_add_test(tc_core, s21_to_lower_test);
  tcase_add_test(tc_core, s21_to_upper_test);
  tcase_add_test(tc_core, s21_atol_test);
  tcase_add_test(tc_core, s21_atold_test);
  tcase_add_test(tc_core, s21_insert_test);
  tcase_add_test(tc_core, s21_trim_test);
  tcase_add_test(tc_core, s21_sscanf_test);
  tcase_add_test(tc_core, s21_memcmp_test);
  tcase_add_test(tc_core, s21_memcpy_test);
  tcase_add_test(tc_core, s21_memset_test);
  tcase_add_test(tc_core, s21_strlen_test);
  tcase_add_test(tc_core, s21_sprintf_test);
  tcase_add_test(tc_core, is_delimiter_test);
  tcase_add_test(tc_core, s21_strchr_test);
  tcase_add_test(tc_core, s21_strrchr_test);
  tcase_add_test(tc_core, s21_strstr_test);
  tcase_add_test(tc_core, s21_strpbrk_test);
  tcase_add_test(tc_core, s21_strtok_test);
  tcase_add_test(tc_core, test_memchr_found_middle);
  tcase_add_test(tc_core, test_memchr_not_found);
  tcase_add_test(tc_core, test_memchr_found_start);
  tcase_add_test(tc_core, test_memchr_empty_string);
  tcase_add_test(tc_core, test_memchr_with_limit);
  tcase_add_test(tc_core, s21_strcspn_test);
  tcase_add_test(tc_core, s21_strncat_test);
  tcase_add_test(tc_core, s21_strncmp_test);
  tcase_add_test(tc_core, s21_strncpy_test);

  suite_add_tcase(s, tc_core);
  return s;
}

int main() {
  int number_failed;
  Suite *s;
  SRunner *sr;
  s = s21_test_suite();
  sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
