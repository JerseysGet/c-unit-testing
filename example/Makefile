TESTER_SRC = ../tester/tester.c

CSTANDARD = -std=gnu2x
COMMON_FLAGS = $(CSTANDARD)

# Flags enabling runtime error for sigsegv and sigfpe might make test output format weird.
TEST_FLAGS = 

TEST_SRCS = main/main_test.c gcd/gcd_test.c
TEST_DEPENDENCY_OBJS = $(TEST_SRCS:_test.c=.o)
TEST_EXECS = $(TEST_SRCS:_test.c=.test)

dbg:
	@echo $(TEST_EXECS)

test: $(TEST_EXECS) $(TEST_DEPENDENCY_OBJS)

%.o: %.c
	@gcc -c $(COMMON_FLAGS) $^ -o $@
	
%.test: %.o %_test.c
	@gcc $(TEST_FLAGS) $(COMMON_FLAGS) $^ $(TESTER_SRC) -o $@
	@./$@

clean:
	rm -f *.test */*.test
	@rm -f *.o */*.o