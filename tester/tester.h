#ifndef __TEST_H
#define __TEST_H

#include <setjmp.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define GREEN(x) "\033[0;32m" x "\033[0m"
#define RED(x) "\033[0;31m" x "\033[0m"
#define BLACK(x) "\033[0;30m" x "\033[0m"
#define YELLOW(x) "\033[0;33m" x "\033[m"

#define GREEN_BOLD(x) "\033[1;32m" x "\033[0m"
#define RED_BOLD(x) "\033[1;31m" x "\033[0m"
#define BLACK_BOLD(x) "\033[1;30m" x "\033[0m"
#define YELLOW_BOLD(x) "\033[1;33m" x "\033[m"

#define WAIT_TEXT "[ " BLACK("..") " ]"
#define OK_TEXT "[ " GREEN("OK") " ]"
#define FAIL_TEXT "[ " RED_BOLD("FAIL") " ]"
#define RTE_TEXT "[ " YELLOW_BOLD("RTE") " ]"

#define FAIL_FORMAT(FORMAT) " expected '" FORMAT "', but found '" FORMAT "' instead "
#define TIME_FORMAT "\t[ %lds ]\n"
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define CLEAR_LINE printf("\r\33[2K");

typedef struct TestReport {
    int totalTests;
    int failedTests;
    time_t testBeginTime;
    time_t testEndTime;
    time_t totalTime;
    bool ranFirstTest;
    struct sigaction sa;
    jmp_buf env_buffer;
    int jmpRet;
} TestReport;

#define __DECLARE_JMP \
    void __jmp_signum(int signum) { longjmp(__report.env_buffer, signum); }

#define INIT_SIGACTION                     \
    __report.sa.sa_handler = __jmp_signum; \
    sigemptyset(&__report.sa.sa_mask);     \
    __report.sa.sa_flags = SA_RESTART;

#define SET_SIGNAL_HANDLER                  \
    sigaction(SIGSEGV, &__report.sa, NULL); \
    sigaction(SIGFPE, &__report.sa, NULL);

#define __DECLARE_INIT_REPORT          \
    void __init_test_report() {        \
        __report.totalTests = 0;       \
        __report.failedTests = 0;      \
        __report.testBeginTime = 0;    \
        __report.testEndTime = 0;      \
        __report.totalTime = 0;        \
        __report.ranFirstTest = false; \
        __report.jmpRet = 0;           \
        INIT_SIGACTION                 \
        SET_SIGNAL_HANDLER             \
    }

#define INIT_TEST        \
    TestReport __report; \
    __DECLARE_JMP        \
    __DECLARE_INIT_REPORT

#define BEGIN_TESTS \
    __init_test_report();

#define SEPARATOR "---------------------------"

#define PRINT_FIRST_MESSAGE               \
    if (!__report.ranFirstTest) {         \
        printf(SEPARATOR);                \
        printf("[ ");                     \
        printf("%s tests", __FILENAME__); \
        printf(" ]");                     \
        printf(SEPARATOR "\n");           \
        __report.ranFirstTest = true;     \
    }

#define PRINT_RUNNING(TEST_NAME)      \
    __report.totalTests++;            \
    printf(WAIT_TEXT);                \
    printf(" Running %s", TEST_NAME); \
    fflush(stdout);

void __test_char(char* testName, char testValue, char expectedValue, TestReport* __report);
void __test_int(char* testName, int testValue, int expectedValue, TestReport* __report);
void __test_long_long(char* testName, long long testValue, long long expectedValue, TestReport* __report);
void __test_string(char* testName, char* testValue, char* expectedValue, TestReport* __report);

#define START_TIMER __report.testBeginTime = time(NULL);
#define END_TIMER __report.testEndTime = time(NULL);
#define PRINT_TIME                                                      \
    printf(TIME_FORMAT, __report.testEndTime - __report.testBeginTime); \
    __report.totalTime += __report.testEndTime - __report.testBeginTime;

#define SET_JMP_PT(TEST_NAME)

#define TEST_EQ(TEST_NAME, TEST_FN, EXPECTED_VALUE)                       \
    PRINT_FIRST_MESSAGE                                                   \
    PRINT_RUNNING(TEST_NAME)                                              \
    SET_JMP_PT(TEST_NAME)                                                 \
    START_TIMER                                                           \
    __report.jmpRet = setjmp(__report.env_buffer);                        \
    if (__report.jmpRet) {                                                \
        CLEAR_LINE                                                        \
        printf(RTE_TEXT);                                                 \
        printf(" %s failed: %s ", TEST_NAME, strsignal(__report.jmpRet)); \
        __report.failedTests++;                                           \
    } else {                                                              \
        __GEN_TEST_EQ(TEST_NAME, TEST_FN, EXPECTED_VALUE)                 \
    }                                                                     \
    END_TIMER                                                             \
    PRINT_TIME

#define __GEN_TEST_EQ(TEST_NAME, TEST_FN, EXPECTED_VALUE) _Generic((TEST_FN), \
    int: __test_int,                                                          \
    long long: __test_long_long,                                              \
    char: __test_char,                                                        \
    char*: __test_string)(TEST_NAME, TEST_FN, EXPECTED_VALUE, &__report);

#define TEST_REPORT                                                \
    printf("%d tests ", __report.totalTests);                      \
    printf("in %lds\n", __report.totalTime);                       \
    if (__report.failedTests == 0) {                               \
        printf(GREEN_BOLD("All Tests Passed"));                    \
    } else {                                                       \
        printf(RED_BOLD("%d Tests Failed"), __report.failedTests); \
    }                                                              \
    printf("\n");
#endif