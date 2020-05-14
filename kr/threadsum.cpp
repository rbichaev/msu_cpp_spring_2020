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
    int number;
    while (true)
    {
        std::unique_lock<std::mutex> lock(mut_num);
        cond.wait(lock, [this](){ return (!num_queue.empty() || off); });
        if (off)
            break;
        number = num_queue.front();
        num_queue.pop();
        lock.unlock();
        sum_ += number;
        std::cout <<sum_<<std::endl;
        
        if (num_queue.empty() && ready == true) break;
    }
}

// организует чтение чисел из файла и запись их в очередь
void ThreadSum::reader()
{
    std::ifstream stream;
    std::string str;
    stream.open(filename);

    std::string number;

    int begin_index = 0;
    int end_index = 0;

    getline(stream, str);

    while (true)
    {
        while (std::string::npos != (begin_index = str.find_first_not_of(' ', end_index)))
        {
            if (std::string::npos == (end_index = str.find_first_of(' ', begin_index)))
                number = str.substr(begin_index);
            else
                number = str.substr(begin_index, end_index - begin_index);

            mut_num.lock();
            num_queue.push(std::stoi(number));
            std::cout << number << std::endl;
            mut_num.unlock();
            cond.notify_one();
        }
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
    std::thread sum(&ThreadSum::summator, this);

    read.join();
    sum.join();

    return sum_;
}
