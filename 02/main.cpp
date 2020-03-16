#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include "parser.h"

int testNum = 0;

// callback функция, вызываемая перед началом парсинга
void beginParse(std::string text)
{
    std::cout << "Начало парсинга строки \"" << text << "\"" << '\n';
}

// callback функция, вызываемая в конце парсинга
void endParse()
{
    std::cout << "Конец парсинга..." << '\n';
}

// callback функция, которая выводит число
void printNum(std::string num)
{
    std::cout << "Это число: " << num << '\n';
}

// callback функция, которая выводит квадрат числа
void printPowNum(std::string num)
{
    std::cout << "Квадрат числа " << num << ": " << pow(stoi(num), 2) << '\n';
}

// callback функция, которая выводит строку
void printStr(std::string str)
{
    std::cout << "Это строка: " << str << '\n';
}

// callback функция, которая выводит буквы строки капсом
void printUpStr(std::string str)
{
    std::cout << "Капс букв строки: ";
    std::transform(str.begin(), str.end(), str.begin(), toupper);
    std::cout << str << "\n";
}

// тест, который выводит числа и строки
void test1()
{
    testNum += 1;
    std::cout << "------\n";
    std::cout << "ТЕСТ " << testNum << "\n";
    std::cout << "------\n";
    std::string text = "44 rt\n5 \t6g tyu";
    registerBeginParse(beginParse);
    // регистрируем callback функцию endParse в зависимости от номера теста
    if (testNum > 1) registerEndParse(endParse);
    registerCallbackNum(printNum);
    registerCallbackStr(printStr);
    if (!parse(text))
        std::cout << "Не все callback функции зарегистрированы!\n";
}

 // тест, который выводит квадраты чисел и строки с капсом
void test2()
{
    testNum += 1;
    std::cout << "------\n";
    std::cout << "ТЕСТ " << testNum << "\n";
    std::cout << "------\n";
    std::string text = "63\tgft 5\nt5w6 bhsy";
    registerBeginParse(beginParse);
    registerEndParse(endParse);
    registerCallbackNum(printPowNum);
    registerCallbackStr(printUpStr);
    if (!parse(text))
        std::cout << "Не все callback функции зарегистрированы!\n";
}

int main()
{
    test1();
    test1();
    test2();
}
