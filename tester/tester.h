#ifndef __TEST_H
#define __TEST_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define GREEN(x) "\033[0;32m" x "\033[0m"
#define RED(x) "\033[0;31m" x "\033[0m"
#define BLACK(x) "\033[0;30m" x "\033[0m"

#define GREEN_BOLD(x) "\033[1;32m" x "\033[0m"
#define RED_BOLD(x) "\033[1;31m" x "\033[0m"
#define BLACK_BOLD(x) "\033[1;30m" x "\033[0m"

#define WAIT_TEXT "[ " BLACK("..") " ]"
#define OK_TEXT "[ " GREEN("OK") " ]"
#define FAIL_TEXT "[ " RED_BOLD("FAIL") " ]"

#define FAIL_FORMAT(FORMAT) " expected '" FORMAT "', but found '" FORMAT "' instead "
#define TIME_FORMAT "\t[ %lds ]\n"
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

typedef struct TestReport {
    int totalTests;
    int failedTests;
    time_t testBeginTime;
    time_t testEndTime;
    bool ranFirstTest;
} TestReport;

#define INIT_TEST \
    TestReport __report = {0, 0, 0, 0, false};

#define INCREMENT_FAIL __report.failedTests++;

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

void __test_int(char* testName, int testValue, int expectedValue, TestReport* __report);
void __test_string(char* testName, char* testValue, char* expectedValue, TestReport* __report);

#define START_TIMER __report.testBeginTime = time(NULL);
#define END_TIMER __report.testEndTime = time(NULL);
#define PRINT_TIME printf(TIME_FORMAT, __report.testEndTime - __report.testBeginTime);

#define TEST_EQ(TEST_NAME, TEST_FN, EXPECTED_VALUE)   \
    PRINT_FIRST_MESSAGE                               \
    START_TIMER                                       \
    PRINT_RUNNING(TEST_NAME)                          \
    __GEN_TEST_EQ(TEST_NAME, TEST_FN, EXPECTED_VALUE) \
    END_TIMER                                         \
    PRINT_TIME

#define __GEN_TEST_EQ(TEST_NAME, TEST_FN, EXPECTED_VALUE) _Generic((EXPECTED_VALUE), \
    int: __test_int,                                                                 \
    char*: __test_string)(TEST_NAME, TEST_FN, EXPECTED_VALUE, &__report);

#define TEST_REPORT                                                \
    printf("%d tests in %s\n", __report.totalTests, __FILENAME__); \
    if (__report.failedTests == 0) {                               \
        printf(GREEN_BOLD("All Tests Passed"));                    \
    } else {                                                       \
        printf(RED_BOLD("%d Tests Failed"), __report.failedTests); \
    }                                                              \
    printf("\n");
#endif