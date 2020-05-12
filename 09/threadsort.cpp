#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <mutex>

#include "threadsort.h"

using num_type = std::vector<uint64_t>;

// считываем элементы [a, b) в вектор vect
bool ThreadSort::get_numbers(num_type &vect, size_t a, size_t b)
{
    std::ifstream stream;
    uint64_t number;
    stream.open(filename, std::ios::binary);
    
    if (!stream)
        return false;

    for (size_t i=0; i<a + b; i++)
    {
        stream.read((char *) &number, sizeof(uint64_t));
        if (i >= a)
            vect.push_back(number);
    }
    stream.close();
    return true;
}

// находим следующий элемент, начиная с которого нужно обработать элементы
void ThreadSort::get_changes(bool &ready, size_t &thr_curr, size_t &thr_step)
{
    while(true)
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
    std::string bin = ".bin";
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
        blockname = block.append(std::to_string(thr_curr)).append(bin);

        mut_blocknames.lock();
        blocknames.push_back(blockname);
        mut_blocknames.unlock();

        o_stream.open(blockname, std::ios::binary);
        if (!o_stream)
        {
            mistake = true;
            break;
        }

        for (size_t i=0; i<thr_step; i++)
            o_stream.write((char *) &vect[i], sizeof(uint64_t));

        o_stream.close();

        mut_bounds.lock();
        get_changes(ready, thr_curr, thr_step);
        mut_bounds.unlock();
    }
}

// функция, которая открывает файлы с отсортированными числами и производит с ними операцию слияния
void ThreadSort::merge()
{
    if (mistake)
    {
        for (size_t j=0; j<blocknames.size(); j++)
            remove(blocknames[j].c_str());
    }

    uint64_t number;
    std::string str;

    std::ofstream result;
    result.open(fileresult, std::ios::binary);

    if (!result)
    {
        mistake = true;

        for (size_t j=0; j<blocknames.size(); j++)
            remove(blocknames[j].c_str());

        return;
    }

    size_t num_of_blocks = blocknames.size();
    std::vector<std::ifstream> blockstreams(num_of_blocks);
    num_type numbers;

    std::vector<uint64_t>::iterator min_iter;
    size_t min_index;

    for (size_t i; i<num_of_blocks; i++)
    {
        blockstreams[i].open(blocknames[i], std::ios::binary);
        if (!blockstreams[i])
        {
            mistake = true;

            for (size_t j=0; j<i-1; j++)
                blockstreams[j].close();

            for (size_t j=0; j<blocknames.size(); j++)
                remove(blocknames[j].c_str());

            return;
        }
        blockstreams[i].read((char *) &number, sizeof(uint64_t));
        numbers.push_back(number);
    }

    while(true)
    {
        min_iter = std::min_element(numbers.begin(), numbers.end());
        min_index = std::abs(std::distance(numbers.begin(), min_iter));

        result.write((char *) &numbers[min_index], sizeof(uint64_t));

        if (!blockstreams[min_index].read((char *) &number, sizeof(uint64_t)))
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
            numbers[min_index] = number;
    }

    result.close();
}

// функция, коорая непосредственно вызывается из main.cpp и запускает процесс сортировки
bool ThreadSort::sort(const std::string &name, const std::string &res, size_t len, size_t st)
{
    filename = name;
    fileresult = res;
    filelen = len;
    step = st;
    mistake = false;

    blocknames.clear();
    used_bounds.clear();

    std::thread first_sort(&ThreadSort::sort_blocks, this);
    std::thread second_sort(&ThreadSort::sort_blocks, this);
    first_sort.join();
    second_sort.join();
    merge();
    return !mistake;
}

