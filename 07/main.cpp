#include <iostream>
#include <iomanip>
#include "vector.h"

// выводим на экран номер теста
void printTest()
{
    static int testNum = 0;
    testNum += 1;
    std::cout << "------" << std::endl;
    std::cout << "ТЕСТ " << testNum << std::endl;
    std::cout << "------" << std::endl;
} 

// выводим значения вектора
template <class TT>
void print(const vector<TT> &vec)
{
    for (int i=0; i<vec.size(); i++)
        std::cout << std::setw(6) << vec[i];
    std::cout << std::endl;
}

// выводим строку
void print(const char *text)
{
    std::cout << text << std::endl;
}

// ТЕСТ_1
void test_1()
{
    printTest();
    vector<int> vec = {1,2,3};
    print("Начальные значение вектора чисел:");
    print(vec);
    vec.resize(5, 11);
    print("Делаем resize до 5 элементов, остатки заполняем 11.");
    print(vec);
    vec.pop_back();
    print("Удаляем последний элемент:");
    print(vec);
}

// ТЕСТ_2
void test_2()
{
    printTest();
    vector<char> vec = {'w', 'n'};
    print("Начальные значение вектора символов:");
    print(vec);
    vec.push_back('z');
    vec.push_back('l');
    print("Добавили в конец два элемента:");
    print(vec);
    vec.erase(vec.begin()+1);
    print("Удаляем второй элемент:");
    print(vec);
}

// ТЕСТ_3
void test_3()
{
    printTest();
    vector<std::string> vec(4, "word");
    print("Начальные значение вектора строк:");
    print(vec);
    vec.push_back("new");
    print("Добавили в конец строку:");
    print(vec);
    vec.resize(7, "empty");
    print("Расширили до 7 элементов:");
    print(vec);
    vec.clear();
    print("Очистили вектор.");
    print("Вектор пуст?");
    std::cout << std::boolalpha << vec.empty() << std::endl;
    std::cout << std::noboolalpha;
}

// ТЕСТ_4 (итератор)
void test_4()
{
    printTest();
    int i = 5;
    int j = 6;
    Iterator<int> iter1(&i);
    Iterator<int> iter2(&j);
    swap(iter1, iter2);
    iter2 -= 6;
    iter2 = 6 + iter2;
    std::cout << *(iter2) << std::endl;
    std::cout << std::boolalpha << (iter2[1] == *(iter2+1)) << std::endl;
    std::cout << std::noboolalpha;
}


int main()
{
    test_1();
    test_2();
    test_3();
    test_4();
}
