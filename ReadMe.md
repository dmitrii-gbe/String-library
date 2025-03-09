# s21_string Library

## Overview
The `s21_string` library is a custom implementation of the C standard library `<string.h>` functions. It provides essential string manipulation functions, memory management functions, and additional utilities, including formatted input/output functions (`sprintf` and `sscanf`).

This library serves as a replacement for standard string functions, offering a self-contained and extensible implementation that adheres to standard C behaviors while allowing custom enhancements.

## Features
- Standard string manipulation functions (e.g., `s21_strlen`, `s21_strcpy`, `s21_strcat`)
- Memory management utilities (e.g., `s21_memcpy`, `s21_memcmp`, `s21_memset`)
- String comparison and search functions (e.g., `s21_strcmp`, `s21_strstr`, `s21_strchr`)
- Extended functionality for formatted string conversion (`s21_sprintf` and `s21_sscanf`), supporting:
  - Basic format specifiers (`%d`, `%f`, `%s`, etc.)
  - Width and precision settings
  - Flags (e.g., `+`, `-`, `0` padding, `#` alternative form)
  - Length modifiers (`h`, `l`, `L`)
  - Custom behavior tuning for specific use cases

## Installation
To use the `s21_string` library in your project, you can compile and link it with your code.

### Compilation
Compile the library:
```sh
make
```
This generates the static (`s21_string.a`) version of the library.

### Usage
To use `s21_string` in your program, include the header file:
```c
#include "s21_string.h"
```

Compile and link against the library:
```sh
gcc -o my_program my_program.c -L. s21_string.a
```

## API Reference
Below is a summary of the functions provided by `s21_string`.

### Memory Functions
- `void *s21_memcpy(void *dest, const void *src, s21_size_t n);`
- `void *s21_memmove(void *dest, const void *src, s21_size_t n);`
- `void *s21_memchr(const void *str, int c, s21_size_t n);`
- `int s21_memcmp(const void *str1, const void *str2, s21_size_t n);`
- `void *s21_memset(void *str, int c, s21_size_t n);`

### String Manipulation
- `s21_size_t s21_strlen(const char *str);`
- `char *s21_strcpy(char *dest, const char *src);`
- `char *s21_strncpy(char *dest, const char *src, s21_size_t n);`
- `char *s21_strcat(char *dest, const char *src);`
- `char *s21_strncat(char *dest, const char *src, s21_size_t n);`
- `char *s21_strchr(const char *str, int c);`
- `char *s21_strrchr(const char *str, int c);`
- `char *s21_strstr(const char *haystack, const char *needle);`
- `int s21_strcmp(const char *str1, const char *str2);`
- `int s21_strncmp(const char *str1, const char *str2, s21_size_t n);`
- `char *s21_strtok(char *str, const char *delim);`

### String Formatting (`s21_sprintf`)
`s21_sprintf` is a custom implementation of `sprintf`, supporting various format specifiers:

**Supported Specifiers:**
- `%d`, `%i` - Signed integers
- `%u` - Unsigned integers
- `%f`, `%F` - Floating point numbers
- `%s` - Strings
- `%c` - Characters
- `%x`, `%X` - Hexadecimal integers
- `%o` - Octal integers
- `%p` - Pointers

**Supported Flags:**
- `-` (Left alignment)
- `+` (Force sign for numbers)
- `0` (Zero padding)
- `#` (Alternate form for hex and octal numbers)

**Example Usage:**
```c
char buffer[100];
s21_sprintf(buffer, "Value: %08d", 42);
printf("%s\n", buffer); // Output: Value: 00000042
```

### String Parsing (`s21_sscanf`)
`s21_sscanf` is a custom implementation of `sscanf`, supporting formatted input parsing.

**Supported Specifiers:**
- `%d`, `%i` - Integer input
- `%f`, `%lf` - Floating point input
- `%s` - String input
- `%c` - Character input

**Example Usage:**
```c
int num;
char str[50];
s21_sscanf("1234 Hello", "%d %s", &num, str);
printf("%d %s\n", num, str); // Output: 1234 Hello
```

##The library provide two additional functions, inspired by String class of C#:
### `s21_insert` function:

```c
void *s21_insert(const char *into, const char *str, s21_size_t start_index);
```

#### Description:
The `s21_insert` function inserts a given string (`str`) into another string (`into`) at a specified starting index (`start_index`). The function performs the following steps:
1. **Initial Validations**: It checks if both `into` and `str` are non-null and if the `start_index` is valid (i.e., it is less than or equal to the length of the `into` string).
2. **Memory Allocation**: It allocates enough memory to hold both the original string (`into`) and the string to be inserted (`str`), ensuring that there is space for the null-terminator.
3. **String Copying**: It then copies the appropriate parts of the strings:
   - It first copies characters from `into` before the insertion point.
   - It copies the `str` to be inserted at the correct position.
   - Finally, it copies the remainder of the `into` string after the insertion point.
4. **Return**: If memory allocation or any other error occurs, it returns `S21_NULL`. Otherwise, it returns the newly created string with the inserted content.

#### Key Points:
- **Memory Allocation**: Uses `calloc` to allocate memory for the new string.
- **String Copying**: Uses `s21_strcpyn` (presumably a custom function) to copy parts of the strings.
- **Error Handling**: Returns `S21_NULL` if there's any error during memory allocation or invalid inputs.
- **Output**: A new string that contains the original string with the insertion made at the specified index.

### `s21_trim` function:

```c
void *s21_trim(const char *src, const char *trim_chars);
```

#### Description:
The `s21_trim` function removes leading and trailing characters from a string (`src`) that match any of the characters in `trim_chars`. If no characters are specified in `trim_chars`, it trims whitespace characters by default. Here's how it works:
1. **Initial Validations**: It checks if both `src` and `trim_chars` are non-null.
2. **Memory Allocation**: It allocates memory for a new string to hold the trimmed result.
3. **Trimming Logic**:
   - If `trim_chars` is not empty, it iterates from the start of `src` to find the first character that is not in `trim_chars`, and similarly iterates from the end to find the first character that is not in `trim_chars`.
   - If `trim_chars` is empty, it defaults to trimming whitespace characters using the `isspace` function.
4. **String Copying**: Once the boundaries of the string to be copied are determined (from `new_start` to `new_end`), the substring is copied into the new string.
5. **Return**: It returns the newly allocated string with the trimmed content. If there's any issue during the process, `S21_NULL` is returned.

#### Key Points:
- **Trimming Logic**: It handles both custom trimming characters (`trim_chars`) or whitespace trimming (using `isspace`).
- **Memory Allocation**: Uses `calloc` to allocate memory for the new string.
- **Error Handling**: Returns `S21_NULL` if memory allocation fails or invalid inputs are encountered.
- **Output**: A new string with the leading and trailing characters removed.

#### Functions Used:
- `s21_strlen`: Presumably calculates the length of the string (equivalent to `strlen`).
- `s21_AnyOf`: A custom function that checks if a character is in the set of `trim_chars`.
- `s21_strcpyn`: A custom string copy function that likely copies a certain number of characters (from one string to another).

---

### Summary:
- **`s21_insert`**: Inserts a string at a specific index in another string, creating a new string.
- **`s21_trim`**: Trims leading and trailing specified characters (or whitespace) from a string.

Let me know if you need more details or clarifications!

## Testing
To run tests for `s21_string`, execute:
```sh
make test
```
This runs a suite of unit tests to validate the correctness of the implemented functions.

## License
This project is released under the MIT License. You are free to use, modify, and distribute it.

## Contributing
Contributions are welcome! If you find a bug or want to propose improvements, please submit an issue or a pull request.
