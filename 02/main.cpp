#include <iostream>
#include <cstring>
#include <cmath>
#include "parser.h"

// callback функция, вызываемая перед началом парсинга
void beginParse(const char *text)
{
    std::cout << "Начало парсинга строки \"" << text << "\"" << '\n';
}

// callback функция, вызываемая в конце парсинга
void endParse()
{
    std::cout << "Конец парсига..." << '\n';
}

// callback функция, которая выводит число
void printNum(char *num)
{
    std::cout << "Это число: " << num << '\n';
}

// callback функция, которая выводит квадрат числа
void printPowNum(char *num)
{
    std::cout << "Квадрат числа " << num << ": " << pow(atoi(num), 2) << '\n';
}

// callback функция, которая выводит строку
void printStr(char *str)
{
    std::cout << "Это строка: " << str << '\n';
}

// callback функция, которая выводит буквы строки капсом
void printUpStr(char *str)
{
    std::cout << "Капс букв строки: ";
    for (int i = 0; str[i]; i++)
    {
        if (isalpha(str[i]))
            std::cout << (char)toupper(str[i]);
        else
            std::cout << str[i];        
    }
    std::cout << "\n";
}

// тест, который выводит числа и строки
void test1()
{
    std::cout << "------\n";
    std::cout << "ТЕСТ 1" << "\n";
    std::cout << "------\n";
    const char *text = "44 rt 5 6g tyu";
    registerBeginParse(beginParse);
    registerEndParse(endParse);
    registerCallbackNum(printNum);
    registerCallbackStr(printStr);
    parse(text);
}

 // тест, который выводит квадраты чисел и строки с капсом
void test2()
{
    std::cout << "------\n";
    std::cout << "ТЕСТ 2" << "\n";
    std::cout << "------\n";
    const char *text = "63 gft 5 t5w6 bhsy";
    registerBeginParse(beginParse);
    registerEndParse(endParse);
    registerCallbackNum(printPowNum);
    registerCallbackStr(printUpStr);
    parse(text);
}

int main()
{
    test1();
    test2();
}
