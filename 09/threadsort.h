#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <mutex>

using num_type = std::vector<uint64_t>;

// класс ThreadSort
// сначала два потока считывают числа блоками, сортируют их и записывают в отдельные файлы
// затем с этими файлами происходит операция слияния
class ThreadSort
{
    std::string filename; // имя файла с исходными данными
    size_t filelen; // длина этого файла
    std::string fileresult; // имя файла, куда записать результат

    std::vector<std::string> blocknames; // имена файлов, куда помещаются отсортированные блоки
    std::vector<size_t> used_bounds; // границы блоков

    std::mutex mut_file; // доступ к файлу с исходынми данными
    std::mutex mut_bounds; // доступ к массиву с границами блоков
    std::mutex mut_blocknames; // доступ к именам блоков

    size_t step; // шаг, с которым считываются блоки

    bool mistake = false; // была ли ошибка при работе с файлами

public:

    ThreadSort()
    {}

    ~ThreadSort()
    {}

    bool get_numbers(num_type &vect, size_t a, size_t b);
    void get_changes(bool &ready, size_t &thr_curr, size_t &thr_step);
    void sort_blocks();
    void merge();
    bool sort(const std::string &name, const std::string &res, size_t len, size_t st);
};
