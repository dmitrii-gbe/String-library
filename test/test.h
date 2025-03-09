#pragma once
#include <assert.h>
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

#define TEST_AR_SIZE 40
#define TEST_STR_SIZE 500
#define FORMAT                                                 \
  "%f %le%12ls%% f%i%%%x g%x%22i%n%14c%ld%hi%*s%n%ls%lX%lx%hx" \
  "%hX"                                                        \
  " %lo%lo%ho%ho%li%hi%lu%e%*i%LG%*1c%p%hd%n"

#define FORMATD_SPRINTF                                                 \
  " Format \"d\" 1st %-+*.*d 2nd %.d 3rd % 20.14d 4th %020d 5th %+020d" \
  " 6th  %-+12.*d 7th %.0d 8th % 20.14d 9th %020d 10th %+020d"          \
  " 11th %-+12.*d 12th %.0d 13th % 20.14d 14th %020d %n 15th %+020d "   \
  "%-15p %-15.10d"

#define FORMATLD_SPRINTF                                                 \
  " Format \"ld\" 1st %-+12.*ld 2nd %.0ld 3rd % 20.14ld 4th %020ld 5th " \
  "%+020ld"                                                              \
  " 6th %-+12.*ld 7th %.0ld 8th % 20.14ld 9th %020ld 10th %+020ld"       \
  " 11th %-+12.*ld 12th %.0ld 13th % 20.14ld 14th %020ld 15th %+020ld"

#define FORMATLI_SPRINTF                                                      \
  " Format \"li\" 1st  %-+12.*li 2nd   %.0li 3rd % 20.14li 4th   %020li 5th " \
  "%+020li"                                                                   \
  " 6th %-+12.*li 7th  %.0li 8th  % 20.14li  9th %020li 10th %+020li"         \
  " 11th %-+12.*li  12th %.0li 13th % 20.14li 14th  %020li    15th %+020li"

#define FORMATLU_SPRINTF                                               \
  " Format \"lu\" 1st %-12.*lu 2nd %.0lu 3rd %20.14lu 4th %020lu 5th " \
  "%020lu"                                                             \
  " 6th %-12.*lu 7th %.0lu 8th %20.14lu 9th %020lu 10th %020lu"        \
  " 11th %-12.*lu 12th %.0lu 13th %20.14lu 14th %020lu 15th %020lu"

#define FORMATLX_SPRINTF                                                 \
  " Format \"lx\" 1st %#-12.*lx 2nd %#.0lx 3rd %20.14lX 4th %020lx 5th " \
  "%020lX"                                                               \
  " 6th %#-12.*lx 7th %#.0lX 8th %20.14lX 9th %#020lx 10th %020lx"       \
  " 11th %#-12.*lx 12th %.0lx 13th %#20.14lx 14th %#020lx 15th %020lx"

#define FORMATLO_SPRINTF                                                       \
  " Format \"lo\" 1st %#-12.*lo 2nd %#.0lo 3rd %20.14lo 4th %020lo 5th %020lo" \
  " 6th %#-12.*lo 7th %#.0lo 8th %20.18lo 9th %#020lo 10th %020lo"             \
  " 11th %#-12.*lo 12th %.0lo 13th %#20.24lo 14th %#020lo 15th %020lo"

#define FORMATHD_SPRINTF                                                 \
  " Format \"hd\" 1st %-+12.*hd 2nd %.0hd 3rd % 20.14hd 4th %020hd 5th " \
  "%+020hd"                                                              \
  " 6th %-+12.*hd 7th %.0hd 8th % 20.14hd 9th %020hd 10th %+020hd"       \
  " 11th %-+12.*hd 12th %.0hd 13th % 20.14hd 14th %020hd 15th %+020hd"

#define FORMATLS_SPRINTF                                        \
  " Format \"s\" 1st %-*.*s 2nd %.0s 3rd %20.14s 4th %*s 5th "  \
  "%20.15s"                                                     \
  " 6th %-12.14s 7th %.*s 8th %20.14s 9th %20s                \
  10th %-*.*ls 11th %.0ls 12th %20.14ls 13th %*ls 14th " \
  "%20.15ls"                                                    \
  " 15th %-12.14ls 16th %.*ls 17th %20.14ls 18th %20ls"

#define ARGLIST_LS                                                          \
  16, 13, str0, str0, str0, 25, str1, str1, str1, 60, str2, str2, str2, 16, \
      13, w_str0, w_str0, w_str0, 25, w_str0, w_str0, w_str0, 60, w_str0,   \
      w_str0, w_str0

#define FORMATS_SPRINTF                                        \
  " Format \"s\" 1st %-*.*s 2nd %.0s 3rd %20.14s 4th %*s 5th " \
  "%20.15s"                                                    \
  " 6th %-12.14s 7th %.*s 8th %20.14s 9th %20s"

#define ARGLIST_S \
  16, 13, str0, str0, str0, 25, str1, str1, str1, 60, str2, str2, str2

#define FORMATLC_SPRINTF                                 \
  " Format \"c\" 1ct %-*c 2nd %c 3rd %20c 4th %*c 5th "  \
  "%20c"                                                 \
  " 6th %-12c 7th %*c 8th %20c 9th %20c                \
  10th %-*lc 11th %lc 12th %20lc 13th %*lc 14th " \
  "%20lc"                                                \
  " 15th %-12lc 16th %*lc 17th %20lc 18th %20lc"

#define ARGLIST_LC                                                          \
  16, c0, c0, c0, 25, c1, c1, c1, 60, c2, c2, c2, 16, w_c0, w_c0, w_c0, 25, \
      w_c1, w_c1, w_c1, 60, w_c2, w_c2, w_c2

#define FORMATC_SPRINTF                                 \
  " Format \"c\" 1ct %-*c 2nd %c 3rd %20c 4th %*c 5th " \
  "%20c"                                                \
  " 6th %-12c 7th %*c 8th %20c 9th %20c"

#define ARGLIST_C 16, c0, c0, c0, 25, c1, c1, c1, 60, c2, c2, c2

#define FORMAT_LONG_DOUBLE                                            \
  "start  %10LE %#10LE %10.0LE %#10.0LE %10.8LE %#10.3LE %#+023.0Le " \
  "%+023.0Le %+-.8LE "                                                \
  "%-+20.Lf %+021.8LF "                                               \
  "\n%#+.3Lg %+.3Lg\n %#+.10Lg  "                                     \
  "\n%#+.0Lg %+.0Lg\n "                                               \
  "%+.8LE %.8Lg "                                                     \
  "%.8Lf "                                                            \
  "%.8Le "                                                            \
  "end"
#define ARG_LIST_LONG_DOUBLE                                              \
  val_long_double, val_long_double, val_long_double, val_long_double,     \
      val_long_double, val_long_double, val_long_double, val_long_double, \
      val_long_double, val_long_double, val_long_double, val_long_double, \
      val_long_double, val_long_double, val_long_double, val_long_double, \
      val_long_double, val_long_double, val_long_double, val_long_double
#define ARG_LIST_LONG_DOUBLE1                                                 \
  val_long_double1, val_long_double1, val_long_double1, val_long_double1,     \
      val_long_double1, val_long_double1, val_long_double1, val_long_double1, \
      val_long_double1, val_long_double1, val_long_double1, val_long_double1, \
      val_long_double1, val_long_double1, val_long_double1, val_long_double1, \
      val_long_double1, val_long_double1, val_long_double1, val_long_double1
#define ARG_LIST_LONG_DOUBLE2                                                 \
  val_long_double2, val_long_double2, val_long_double2, val_long_double2,     \
      val_long_double2, val_long_double2, val_long_double2, val_long_double2, \
      val_long_double2, val_long_double2, val_long_double2, val_long_double2, \
      val_long_double2, val_long_double2, val_long_double2, val_long_double2, \
      val_long_double2, val_long_double2, val_long_double2, val_long_double2
#define ARG_LIST_LONG_DOUBLE3                                                 \
  val_long_double3, val_long_double3, val_long_double3, val_long_double3,     \
      val_long_double3, val_long_double3, val_long_double3, val_long_double3, \
      val_long_double3, val_long_double3, val_long_double3, val_long_double3, \
      val_long_double3, val_long_double3, val_long_double3, val_long_double3, \
      val_long_double3, val_long_double3, val_long_double3, val_long_double3
/*#define ARG_LIST_LONG_DOUBLE4 \
  val_long_double4, val_long_double5, val_long_double6, val_long_double7,     \
      val_long_double4, val_long_double5, val_long_double6, val_long_double7, \
      val_long_double4, val_long_double5, val_long_double6, val_long_double7, \
      val_long_double4, val_long_double5, val_long_double6, val_long_double7, \
      val_long_double4, val_long_double5, val_long_double6, val_long_double7
*/
#define FORMAT_DOUBLE                                          \
  "start  %10E %#10E %10.0E %#10.0E %10.8E %#10.8E %#+023.0e " \
  "%+023.0e %+-.8E "                                           \
  "%-+20.f %+021.8F "                                          \
  "\n%#+.3g %+.3g\n %#+.10g  "                                 \
  "\n%#+.0g %+.0g\n "                                          \
  "%+.8E %.8g "                                                \
  "%.8f "                                                      \
  "%.6e "                                                      \
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
/*#define ARG_LIST_DOUBLE4                                               \
  val_double4, val_double5, val_double6, val_double7, val_double4,     \
      val_double5, val_double6, val_double7, val_double4, val_double5, \
      val_double6, val_double7, val_double4, val_double5, val_double6, \
      val_double7, val_double4, val_double5, val_double6, val_double7
*/
void AtolTest();
void AtoldTest();
void Test();
int StrEq(const char *str1, const char *str2, int len);
char **InitArr(const int rows, const int cols);
void DestroyArr(char **const arr, const int rows);
