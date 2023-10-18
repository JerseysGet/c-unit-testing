#include "gcd.h"

#include "../../tester/tester.h"

INIT_TEST

void gcdTest1() {
    TEST_EQ("gcd test 1", gcd(0, 10), 10);
}

void gcdTest2() {
    TEST_EQ("gcd test 2", gcd(5, 10), 5);
}

void gcdTest3() {
    TEST_EQ("gcd test 3", gcd(17, 127), 1);
}

void gcdTests() {
    gcdTest1();
    gcdTest2();
    gcdTest3();
}

int main() {
    gcdTests();
}