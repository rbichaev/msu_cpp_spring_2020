#include <iostream>
#include <chrono>
#include <assert.h>
#include <ctime>
#include "threadpool.h"

//вывод в поток
template <class T>
void print(const T &obj)
{
    std::cout << obj << std::endl;
}

// запускаемые функции
int foo1(int a)
{
    std::this_thread::sleep_for (std::chrono::seconds(5));
    return (a + 2);
}

int foo2()
{
    return 5;
}

std::string foo3(std::string word)
{
    std::this_thread::sleep_for (std::chrono::seconds(5));
    return word.append("put");
}

// суть проверки:
// запускаем несколько функций с пулами, потом без них
// сравниваем выводимые значения с ожидаемыми
// сравниваем время работы (в секундах) с пулами и без
// при заданных функциях время работы на пулах должно быть меньше
int main()
{
    ThreadPool pool(3);

    time_t begin_time;
    time_t end_time;
    time_t res1;
    time_t res2;

    time(&begin_time);

    auto task1 = pool.exec(foo1, 5);
    auto task2 = pool.exec([]() { return 1; });
    auto task3 = pool.exec(foo2);
    auto task4 = pool.exec(foo3, "out");

    assert (task1->get() == 7);
    assert (task2->get() == 1);
    assert (task3->get() == 5);
    assert (task4->get() == "output");

    time(&end_time);

    res1 = difftime(end_time, begin_time);
    print("Время при работе с пулами:");
    print(res1);

    auto foo = []() { return 1; };

    time(&begin_time);

    int a = foo1(5);
    int b = foo();
    int c = foo2();
    std::string d = foo3("out");

    time(&end_time);

    res2 = difftime(end_time, begin_time);
    print("Время при работе без пулов:");
    print(res2);

    assert (res1 < res2);

    print("Тесты пройдены!");
}
