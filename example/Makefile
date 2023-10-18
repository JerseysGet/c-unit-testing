# CC = gcc
# CSTANDARD = -std=gnu2x
# CFLAGS = $(CSTANDARD)

TESTER_SRC = ../tester/tester.c

FILES = main/main.c gcd/gcd.c
FILE_OBJS = $(FILES:.c=.o)
FILE_TEST_SRCS = $(FILES:.c=_test.c)
FILE_TEST_EXECS = $(FILES:.c=.test)

lol:
	@echo $(FILE_TEST_EXECS)

test: $(FILE_TEST_EXECS)
	
%.test: %.c %_test.c
	@gcc $^ $(TESTER_SRC) -o $@
	@./$@

clean:
	rm -f *.test */*.test
	rm -f *.o */*.o