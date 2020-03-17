#include <iostream>
#include <algorithm>
#include <string>
// #include <cmath>
#include "parser.h"

int testNum = 0;

// переменные для проверки, встретились ли в данной строке числа и строки
bool wereNums;
bool wereStrs;

// callback функции, вызываемые перед началом парсинга
void beginParseNum(const std::string &text)
{
    wereNums = false;
    std::cout << "Начало парсинга: поиск токенов-чисел в стоке \"" << text << "\"" << '\n';
}

void beginParseStr(const std::string &text)
{
    wereStrs = false;
    std::cout << "Начало парсинга: поиск токенов-строк в строке \"" << text << "\"" << '\n';
}

// callback функции, вызываемые в конце парсинга
void endParseNum()
{
    if (!wereNums)
        std::cout << "В этой строке токены-числа не найдены!\n";
    std::cout << "Конец парсинга..." << '\n';
}

void endParseStr()
{
    if (!wereStrs)
        std::cout << "В этой строке токены-строки не найдены!\n";
    std::cout << "Конец парсинга..." << '\n';
}

// callback функция, которая выводит число
void printNum(int num)
{
    if (!wereNums)
    {
        wereNums = true;
        std::cout << "Найдены числа:\n";
    }
    std::cout << num << '\n';
}

// callback функция, которая ничего не делает с числом
void passNum(int num) {}

// callback функция, которая выводит строку
void printStr(const std::string &str)
{
    if (!wereStrs)
    {
        wereStrs = true;
        std::cout << "Найдены строки:\n";
    }
    std::cout << str << '\n';
}

// callback функция, которая ничего не делает со строкой
void passStr(const std::string &str) {}

// тест, который ищет числа
void test1()
{
    testNum += 1;
    std::cout << "------\n";
    std::cout << "ТЕСТ " << testNum << "\n";
    std::cout << "------\n";
    const std::string text = "44 rt\n5 \t6g tyu 523\nty6\t903 46";
    registerBeginParse(beginParseNum);
    // регистрируем callback функцию endParse в зависимости от номера теста
    if (testNum > 1) registerEndParse(endParseNum);
    registerCallbackNum(printNum);
    registerCallbackStr(passStr);
    if (!parse(text))
        std::cout << "Не все callback функции зарегистрированы!\n";
}

 // тест, который ищет строки
void test2()
{
    testNum += 1;
    std::cout << "------\n";
    std::cout << "ТЕСТ " << testNum << "\n";
    std::cout << "------\n";
    const std::string text = "63\tgft 5\nt5w6 bhsy fbds\n67\t7ydre oi";
    registerBeginParse(beginParseStr);
    registerEndParse(endParseStr);
    registerCallbackNum(passNum);
    registerCallbackStr(printStr);
    if (!parse(text))
        std::cout << "Не все callback функции зарегистрированы!\n";
}

// тест, который ищет числа, но они отсутствуют
void test3()
{
    testNum += 1;
    std::cout << "------\n";
    std::cout << "ТЕСТ " << testNum << "\n";
    std::cout << "------\n";
    const std::string text = "5rt\nyhu8f\tyyuij hgfd\nttyh\tdgg";
    registerBeginParse(beginParseNum);
    registerEndParse(endParseNum);
    registerCallbackNum(printNum);
    registerCallbackStr(passStr);
    if (!parse(text))
        std::cout << "Не все callback функции зарегистрированы!\n";
}

 // тест, который ищет строки, но они отсутствуют
void test4()
{
    testNum += 1;
    std::cout << "------\n";
    std::cout << "ТЕСТ " << testNum << "\n";
    std::cout << "------\n";
    const std::string text = "4 56\t68\n43 89\n7 43\t9 78";
    registerBeginParse(beginParseStr);
    registerEndParse(endParseStr);
    registerCallbackNum(passNum);
    registerCallbackStr(printStr);
    if (!parse(text))
        std::cout << "Не все callback функции зарегистрированы!\n";
}

int main()
{
    test1();
    test1();
    test2();
    test3();
    test4();
}
