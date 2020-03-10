#include <iostream>
#include <cstdlib>
#include "alloc.h"

using namespace std;

int numTest = 0;

// этот тип теста показывает работу программы с использованием одной
// переменной и без использования функции reset()
void test1(int maxSize, int num)
{
    numTest += 1;
    cout << "------\n";
    cout << "ТЕСТ " << numTest << "\n";
    cout << "------\n";
    cout << "Значение maxSize: " << maxSize << "\n";
    if (makeAllocator(maxSize))
    {
        cout << "Ошибка выделения памяти!\n";
        return;
    }
    cout << "Число байт для массива: " << num << "\n";
    char *c = alloc(num);
    if (c == nullptr)
    {
        cout << "Выход за пределы выделенной памяти!\n";
    }
    freeAllocator();
}

// этот тип теста показывает работу программы с созданием двух переменных
// и использованием функции reset() в случае, когда на вторую переменную
// не хватает памяти
void test2(int maxSize, int num1, int num2)
{
    numTest += 1;
    cout << "------\n";
    cout << "ТЕСТ " << numTest << "\n";
    cout << "------\n";
    cout << "Значение maxSize: " << maxSize << "\n";
    if (makeAllocator(maxSize))
    {
        cout << "Ошибка выделения памяти!\n";
        return;
    }
    cout << "Число байт для 1 массива: " << num1 << "\n";
    char *c1 = alloc(num1);
    if (c1 == nullptr)
    {
        cout << "Выход за пределы выделенной памяти!\n";
    }
    cout << "Число байт для 2 массива: " << num2 << "\n";
    char *c2 = alloc(num2);
    if (c2 == nullptr)
    {
        cout << "Выход за пределы выделенной памяти!\n";
        cout << "Освобождение памяти первой переменной...\n";
        reset();
        c2 = alloc(num2);
        if (c2 != nullptr)
        {
            cout << "Вторая переменная успешно записана!\n";
        }
        else
        {
            cout << "Вторая переменная занимает больше изначально выделенной памяти!\n";
        }
    }
    freeAllocator();
}

int main()
{
    test1(4, 5);
    test1(5, 4);
    test2(5, 2, 3);
    test2(5, 3, 4);
    test2(5, 3, 6);
}