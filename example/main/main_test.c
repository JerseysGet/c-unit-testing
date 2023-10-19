#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../tester/tester.h"

INIT_TEST

void factorialTest1() {
    TEST_EQ("Fac Test 1", factorial(0), 1);
}

void factorialTest2() {
    TEST_EQ("Fac Test 2", factorial(2), 2);
}

void factorialTest3() {
    TEST_EQ("Fac Test 3", factorial(6), 720);
}

void factorialTests() {
    factorialTest1();
    factorialTest2();
    factorialTest3();
}

void stringTest1() {
    char* ret = string();
    TEST_EQ("String Test 1", ret, "test");
    free(ret);
}

void stringTest2() {
    char* ret = string();
    TEST_EQ("String Test 2", ret, "not test");
    free(ret);
}

void stringTests() {
    stringTest1();
    stringTest2();
}

char charFunc() {
    sleep(2);
    int* ptr = 0x0;
    *ptr = 1;
    return 'a';
}

long long longLongtest() {
    return __LONG_LONG_MAX__;
}

long long fpeTest() {
    long long num = 1;
    long long den = 0;
    return num / den;
}

int main() {
    BEGIN_TESTS
    factorialTests();
    stringTests();
    TEST_EQ("sample char test", charFunc(), 'c');
    TEST_EQ("sample ll test", longLongtest(), __LONG_LONG_WIDTH__);
    TEST_EQ("sample rte test", fpeTest(), __LONG_LONG_MAX__);
    TEST_REPORT
}