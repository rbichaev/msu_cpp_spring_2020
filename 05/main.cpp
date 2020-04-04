#include <iostream>
#include "bigint.h"


// выводим на экран номер теста
void printTest()
{
    static int testNum = 0;
    testNum += 1;
    std::cout << "------" << std::endl;
    std::cout << "ТЕСТ " << testNum << std::endl;
    std::cout << "------" << std::endl;
}

void print(const BigInt &bint_1, const BigInt &bint_2, const char *operation, const BigInt &result)
{
    std::cout << bint_1 << " " << operation << " " << bint_2 << " = " << result << std::endl;
}

void print(const BigInt &bint_1, const BigInt &bint_2, const char *operation, bool result)
{
    std::cout << bint_1 << " " << operation << " " << bint_2 << " = " << std::boolalpha << result << std::endl;
    std::cout << std::noboolalpha;
}

void print(const BigInt &bint, const char *operation, const BigInt &result)
{
    std::cout << operation << " " << bint << " = " << result << std::endl;
}

void test_add(const char* num_1, const char *num_2)
{
    printTest();
    BigInt bint_1 = num_1;
    BigInt bint_2 = num_2;
    BigInt r = bint_1 + bint_2;
    print(bint_1, bint_2, "+", r);
}

void test_sub(const char* num_1, const char *num_2)
{
    printTest();
    BigInt bint_1 = num_1;
    BigInt bint_2 = num_2;
    BigInt r = bint_1 - bint_2;
    print(bint_1, bint_2, "-", r);
}

void test_less(const char* num_1, const char *num_2)
{
    printTest();
    BigInt bint_1 = num_1;
    BigInt bint_2 = num_2;
    bool r = (bint_1 < bint_2);
    print(bint_1, bint_2, "<", r);
}

void test_more(const char* num_1, const char *num_2)
{
    printTest();
    BigInt bint_1 = num_1;
    BigInt bint_2 = num_2;
    bool r = (bint_1 > bint_2);
    print(bint_1, bint_2, ">", r);
}

void test_lesseq(const char* num_1, const char *num_2)
{
    printTest();
    BigInt bint_1 = num_1;
    BigInt bint_2 = num_2;
    bool r = (bint_1 <= bint_2);
    print(bint_1, bint_2, "<=", r);
}

void test_moreeq(const char* num_1, const char *num_2)
{
    printTest();
    BigInt bint_1 = num_1;
    BigInt bint_2 = num_2;
    bool r = (bint_1 >= bint_2);
    print(bint_1, bint_2, ">=", r);
}

void test_unsub(const char *num)
{
    printTest();
    BigInt bint = num;
    BigInt r = -bint;
    print(bint, "-", r);
}

int main()
{
    test_add("-245", "45");
    test_sub("-245", "45");
    test_less("-245", "45");
    test_more("-245", "45");
    test_lesseq("-245", "45");
    test_moreeq("-245", "45");
    test_unsub("-245");
}
