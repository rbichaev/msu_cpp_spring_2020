#include <iostream>
#include <cstring>
#include "parser.h"

// объявляем имена указателей на регистрируемые callback функции
void (*beginParse)(const char *);
void (*endParse)();
void (*numParse)(char *); 
void (*strParse)(char *); 

// регистрируем начало парсинга
void registerBeginParse(void (*callbackFoo)(const char *))
{
    beginParse = callbackFoo;
}

// регистрируем конец парсинга
void registerEndParse(void (*callbackFoo)())
{
    endParse = callbackFoo;
}

// регистрируем callback для числа
void registerCallbackNum(void (*callbackFoo)(char *))
{
    numParse = callbackFoo;
}

// регистрируем callback для строки
void registerCallbackStr(void (*callbackFoo)(char *))
{
    strParse = callbackFoo;
}

// парсинг
void parse(const char *text)
{
    char *copy = strdup(text);
    char *word = strtok(copy, "\n\t ");
    bool isNum;  // это флаг для проверки на число
    beginParse(text);
    while(word != NULL)
    {
        // полагаем, что word - число, и проверяем его поэлементно
        isNum = 1;
        for (int i = 0; i < strlen(word); i++)
        {
            if (!isdigit(word[i]))
            {
                isNum = 0;
                strParse(word);
                break;
            }
        }
        if (isNum == 1)
            numParse(word);
        word = strtok(NULL, "\n\t ");
    }
    endParse();
}

