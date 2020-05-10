#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <mutex>

#include "threadsort.h"

using num_type = std::vector<uint64_t>;

// считываем строки [a, b) в вектор vect
bool ThreadSort::get_numbers(num_type &vect, size_t a, size_t b)
{
    std::fstream stream;
    stream.open(filename);

    if (!stream)
        return false;
        
    std::string str;

    for (size_t i=0; i<a + b; i++)
    {
        getline(stream, str);
        if (i >= a)
            vect.push_back(std::stoi(str));
    }
    stream.close();
    return true;
}

// находим следующий элемент, начиная с которого нужно обработать элементы
void ThreadSort::get_changes(bool &ready, size_t &thr_curr, size_t &thr_step)
{
    while(1)
    {
        std::vector<size_t>::iterator it = std::find(used_bounds.begin(), used_bounds.end(), thr_curr);
        if (it != used_bounds.end())
        {
            if (thr_curr + thr_step < filelen)
                thr_curr += thr_step;
            else
            {
                ready = true;
                break;
            }
        }
        else
        {
            if (thr_curr + thr_step > filelen)
                thr_step = filelen - thr_curr;

            used_bounds.push_back(thr_curr);
            break; 
        }       
    }
}

// функция, которая считывает числа блоками, сортирует, и записывает в отдельные файлы
void ThreadSort::sort_blocks()
{
    size_t thr_curr = 0;
    size_t thr_step = step;

    bool ready = false;

    mut_bounds.lock();
    get_changes(ready, thr_curr, thr_step);
    mut_bounds.unlock();

    num_type vect;

    std::string block = "block";
    std::string txt = ".txt";
    std::string blockname;

    std::ofstream o_stream;

    while(!ready)
    {
        vect.clear();
        mut_file.lock();
        if (!get_numbers(vect, thr_curr, thr_step))
        {
            mistake = true;
            break;
        }
        mut_file.unlock();

        std::sort(vect.begin(), vect.end());

        block = "block";
        blockname = block.append(std::to_string(thr_curr)).append(txt);

        mut_blocknames.lock();
        blocknames.push_back(blockname);
        mut_blocknames.unlock();

        o_stream.open(blockname);
        if (!o_stream)
        {
            mistake = true;
            break;
        }

        for (size_t i=0; i<thr_step; i++)
            o_stream << vect[i] << std::endl;

        o_stream.close();

        mut_bounds.lock();
        get_changes(ready, thr_curr, thr_step);
        mut_bounds.unlock();
    }
}

// функция, которая открывает файлы с отсортированными числами и производит с ними операцию слияния
void ThreadSort::merge()
{
    uint64_t number;
    std::string str;

    std::ofstream result;
    result.open("result.txt");

    if (!result)
    {
        mistake = true;
        return;
    }

    size_t num_of_blocks = blocknames.size();
    std::vector<std::fstream> blockstreams(num_of_blocks);
    num_type numbers;

    std::vector<uint64_t>::iterator min_iter;
    size_t min_index;

    for (size_t i; i<num_of_blocks; i++)
    {
        blockstreams[i].open(blocknames[i]);
        if (!blockstreams[i])
        {
            mistake = true;
            return;
        }
        getline(blockstreams[i], str);
        number = std::stoi(str);
        numbers.push_back(number);
    }

    while(1)
    {
        min_iter = std::min_element(numbers.begin(), numbers.end());
        min_index = std::abs(std::distance(numbers.begin(), min_iter));

        result << numbers[min_index] << std::endl;

        getline(blockstreams[min_index], str);
        if (str.size() == 0)
        {
            blockstreams[min_index].close();
            remove(blocknames[min_index].c_str());

            blockstreams.erase(blockstreams.begin() + min_index);

            blocknames.erase(blocknames.begin() + min_index);

            numbers.erase(numbers.begin() + min_index);

            num_of_blocks -= 1;

            if (num_of_blocks == 0)
                break;
        }
        else
            numbers[min_index] = std::stoi(str);
    }

    result.close();
}

// функция, коорая непосредственно вызывается из main.cpp и запускает процесс сортировки
bool ThreadSort::sort()
{
    std::thread first_sort(&ThreadSort::sort_blocks, this);
    std::thread second_sort(&ThreadSort::sort_blocks, this);
    first_sort.join();
    second_sort.join();
    merge();
    return !mistake;
}

