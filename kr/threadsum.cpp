#include <iostream>
#include <functional>
#include <fstream>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <sstream>

#include "threadsum.h"

void ThreadSum::summator()
{
    std::string numbers;
    while (true)
    {
        std::unique_lock<std::mutex> lock(mut_num);
        cond.wait(lock, [this](){ return (!num_queue.empty() || ready); });
        if (ready && num_queue.empty())
            break;
        numbers = num_queue.front();
        num_queue.pop();
        lock.unlock();

        std::string number;
        int begin_index = 0;
        int end_index = 0;

        while (std::string::npos != (begin_index = numbers.find_first_not_of(' ', end_index)))
        {
            if (std::string::npos == (end_index = numbers.find_first_of(' ', begin_index)))
                number = numbers.substr(begin_index);
            else
                number = numbers.substr(begin_index, end_index - begin_index);

            mut_num.lock();
            sum_ += std::stoi(number);
            
            mut_num.unlock();
        }

        mut_sum.lock();
        if (num_queue.empty() && ready == true) 
        {
            mut_sum.unlock();
            break;
        }
        mut_sum.unlock();
    }
}        

// организует чтение чисел из файла и запись их в очередь
void ThreadSum::reader()
{
    std::ifstream stream;
    std::string str;
    stream.open(filename);

    std::string number;

    getline(stream, str);

    while (true)
    {
        mut_sum.lock();
        num_queue.push(str);
        cond.notify_one();
        mut_sum.unlock();
        getline(stream, str);
        if (!stream)
            break;
    }
    ready = true;
    cond.notify_one();
    stream.close();
}

// вызывается из main
int ThreadSum::sum_numbers(const std::string &name)
{
    filename = name;
    sum_ = 0;

    std::thread read(&ThreadSum::reader, this);
    std::thread sum1(&ThreadSum::summator, this);
    std::thread sum2(&ThreadSum::summator, this);

    read.join();
    sum1.join();
    sum2.join();

    return sum_;
}
