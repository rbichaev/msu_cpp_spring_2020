#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include "parser.h"

// объявляем имена указателей на регистрируемые callback функции{
beginParse beginParseCallback;
endParse endParseCallback;
numParse numParseCallback;
strParse strParseCallback;

// вводим переменные для проверки - были ли зарегистрированы callback функции
bool beginParseDeclared = false;
bool endParseDeclared = false;
bool numParseDeclared = false;
bool strParseDeclared = false;

// регистрируем начало парсинга
void registerBeginParse(beginParse callbackFoo)
{
    beginParseCallback = callbackFoo;
    beginParseDeclared = true;
}

// регистрируем конец парсинга
void registerEndParse(endParse callbackFoo)
{
    endParseCallback = callbackFoo;
    endParseDeclared = true;
}

// регистрируем callback для числа
void registerCallbackNum(numParse callbackFoo)
{
    numParseCallback = callbackFoo;
    numParseDeclared = true;
}

// регистрируем callback для строки
void registerCallbackStr(strParse callbackFoo)
{
    strParseCallback = callbackFoo;
    strParseDeclared = true;
}

// парсинг
bool parse(const std::string text)
{
    // проверяем, зарегистрированы ли все callback функции
    if ((beginParseDeclared & endParseDeclared & numParseDeclared & strParseDeclared) == false)
        return false;

    beginParseCallback(text);

    int begin_index = 0;
    int end_index = 0;
    std::string word;
    const std::string separators("\n\t ");

    // цикл парсинга
    while (std::string::npos != (begin_index = text.find_first_not_of(separators, end_index)))
    {
        if (std::string::npos == (end_index = text.find_first_of(separators, begin_index)))
            word = text.substr(begin_index);
        else
            word = text.substr(begin_index, end_index - begin_index);

        // проверяем, число ли это
        if (std::all_of(word.begin(), word.end(), isdigit))
            numParseCallback(word);
        else
            strParseCallback(word);
    }
    endParseCallback();
    return true;
}

