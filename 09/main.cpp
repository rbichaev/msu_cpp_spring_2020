#include <iostream>
#include <string>
#include <array>
#include "threadsort.h"

// выводим на экран номер теста
void print_test()
{
    static int test_num = 0;
    test_num += 1;
    std::cout << "------" << std::endl;
    std::cout << "ТЕСТ " << test_num << std::endl;
    std::cout << "------" << std::endl;
}

void check_result(const std::string &filename, const std::vector<uint64_t> nums)
{
    print_test();

    std::ifstream stream;
    uint64_t number;

    bool mistake = false;

    stream.open(filename);
    for (size_t i=0; i<nums.size(); i++)
    {
        stream.read((char *) &number, sizeof(uint64_t));

        if (number != nums[i])
        {
            std::cout << "WRONG!" << std::endl;
            mistake = true;
            break;
        }
    }

    if (!mistake)
        std::cout << "Well done!" << std::endl;

    stream.close();
}

int main()
{
    ThreadSort sorter;
    std::ofstream stream;

    // ТЕСТ_1
    std::vector<uint64_t> nums1 = {5, 3, 2, 1, 67, 32, 4, 8, 0, 12, 12, 45, 322};
    std::vector<uint64_t> res1 = {0, 1, 2, 3, 4, 5, 8, 12, 12, 32, 45, 67, 322};

    stream.open("vals1.bin", std::ios::binary);
    for (size_t i=0; i<nums1.size(); i++)
        stream.write((char *) &nums1[i], sizeof(uint64_t));
    stream.close();

    if (!sorter.sort("vals1.bin", "result1.bin", 13, 5))
        std::cout << "ПРИ РАБОТЕ С ФАЙЛАМИ ПРОИЗОШЛА ОШИБКА" << std::endl;
    else
    {
        check_result("result1.bin", res1);
    }


    // ТЕСТ_2
    std::vector<uint64_t> nums2 = {134, 56, 78, 234, 6, 0, 9, 2, 2, 2, 4578, 4, 3, 2, 66, 8, 9, 0, 53, 230};
    std::vector<uint64_t> res2 = {0, 0, 2, 2, 2, 2, 3, 4, 6, 8, 9, 9, 53, 56, 66, 78, 134, 230, 234, 4578};

    stream.open("vals2.bin", std::ios::binary);
    for (size_t i=0; i<nums2.size(); i++)
        stream.write((char *) &nums2[i], sizeof(uint64_t));
    stream.close();

    if (!sorter.sort("vals2.bin", "result2.bin", 20, 5))
        std::cout << "ПРИ РАБОТЕ С ФАЙЛАМИ ПРОИЗОШЛА ОШИБКА" << std::endl;
    else
    {
        check_result("result2.bin", res2);
    }

    // ТЕСТ_3
    size_t max_size = 100000;

    // создаем массив из чисел от 0 до (max_size - 1)
    std::vector<uint64_t> res3;
    for (size_t i=0; i<max_size; i++)
        res3.push_back(i);
    
    // сортировать будем массив чисел от (max_size - 1) до 0
    std::vector<uint64_t> nums3;
    for (size_t i=0; i<max_size; i++)
        nums3.push_back(max_size - 1 - res3[i]);

    stream.open("vals3.bin", std::ios::binary);
    for (size_t i=0; i<nums3.size(); i++)
        stream.write((char *) &nums3[i], sizeof(uint64_t));
    stream.close();

    if (!sorter.sort("vals3.bin", "result3.bin", max_size, 100))
        std::cout << "ПРИ РАБОТЕ С ФАЙЛАМИ ПРОИЗОШЛА ОШИБКА" << std::endl;
    else
    {
        check_result("result3.bin", res3);
    }
}