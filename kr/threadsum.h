#include <iostream>
#include <functional>
#include <fstream>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

// класс ThreadSum
class ThreadSum
{
    bool off = false;
    bool ready = false;

    std::mutex mut_num;
    std::mutex mut_sum;
    std::condition_variable cond;

    std::queue<int> num_queue; // очередь с числами, которые подлежат суммированию

    std::string filename; // имя файла, откуда идет считывание

    int sum_ = 0;

    // организует суммирование в переменную sum_
    void summator();

    // организует чтение чисел из файла и запись их в очередь
    void reader();

public:

    ThreadSum()
    {}

    ~ThreadSum()
    {}

    // вызывается из main
    int sum_numbers(const std::string &name);

};
