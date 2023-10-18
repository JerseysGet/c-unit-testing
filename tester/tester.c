#include "tester.h"

void clearLine() {
    printf("\r\33[2K");
}

void okMessage(char* testName) {
    printf(OK_TEXT);
    printf(" %s passed", testName);
}

void failMessage(char* testName, TestReport* __report) {
    __report->failedTests++;
    printf(FAIL_TEXT);
    printf(" %s failed,", testName);
}

void __test_int(char* testName, int testValue, int expectedValue, TestReport* __report) {
    clearLine();
    if (testValue == expectedValue) {
        okMessage(testName);
    } else {
        failMessage(testName, __report);
        printf(FAIL_FORMAT("%d"), expectedValue, testValue);
    }
}

void __test_string(char* testName, char* testValue, char* expectedValue, TestReport* __report) {
    clearLine();
    if (strcmp(testValue, expectedValue) == 0) {
        okMessage(testName);
    } else {
        failMessage(testName, __report);
        printf(FAIL_FORMAT("%s"), expectedValue, testValue);
    }
}