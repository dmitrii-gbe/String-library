ifeq ($(origin CC),default)
	CC = gcc
endif

CFLAGS ?= -O3 -Wall -Werror -Wextra -std=c11
# CFLAGS ?= -g -std=c11
COBJ_DIR = ./object_files
BINDIR := .
STATIC_LIB = s21_string.a
TEST = ./test
LIBS = -lcheck -lm
CSRC = s21_sprintf.c s21_sscanf_extra.c s21_strcspn.c s21_strerror.c s21_strncat.c s21_strncmp.c s21_strncpy.c s21_memory.c s21_search_and_tokenization.c
TEST_CSRC := $(TEST)/test.c
COBJ := $(addprefix $(COBJ_DIR)/,$(CSRC:.c=.o))
TEST_COBJ := $(TEST_CSRC:.c=.o)
DEPS := $(COBJ:.o=.d)
TEST_DEPS := $(TEST_COBJ:.o=.d)

ifeq ($(shell uname -s),Linux)
	LIBS += -lsubunit
endif

.PHONY: all clean test gcov_report

all: s21_string.a test gcov_report

$(COBJ) : $(COBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_COBJ) : $(TEST)/%.o : $(TEST)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(DEPS) : $(COBJ_DIR)/%.d : %.c
	@mkdir -p $(@D)
	$(CC) -E $(CFLAGS) $< -MM -MT $(@:.d=.o) > $@

$(TEST_DEPS) : $(TEST)/%.d : $(TEST)/%.c
	@mkdir -p $(@D)
	$(CC) -E $(CFLAGS) $< -MM -MT $(@:.d=.o) > $@

$(BINDIR)/$(STATIC_LIB): $(COBJ) 
	ar -rcs $@ $^ 

test: $(TEST_COBJ) $(BINDIR)/s21_string.a
	$(CC) $(CFLAGS) $< -L. s21_string.a $(LIBS) -o $(TEST)/test
	@${TEST}/test

gcov_report: $(BINDIR)/$(CSRC) $(TEST)/test.c
	@$(CC) -fprofile-arcs -ftest-coverage $(CFLAGS) $^ -o $(TEST)/test $(LIBS)
	@${TEST}/test
	@lcov -t "gcov_report" -o gcov_report.info -c -d . 
	@genhtml -o gcov_report gcov_report.info
	@open gcov_report/index.html

clean:
	@rm -rf $(COBJ_DIR)
	@rm -f ./*.a
	@rm -f test/*.gcda
	@rm -f test/*.gcno
	@rm -f *.gcda
	@rm -f *.gcno
	@rm -f *.info
	@rm -rf -f gcov_report/
	@rm -f $(TEST)/test $(TEST)/test.o $(TEST)/test.d

NODEPS = clean

ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
	include $(TEST_DEPS)
	include $(DEPS)
endif

rebuild:
	@make clean
	@make all
