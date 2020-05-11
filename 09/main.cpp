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
    std::string str;

    bool mistake = false;

    stream.open(filename);
    for (size_t i=0; i<nums.size(); i++)
    {
        getline(stream, str);
        if (std::stoi(str) != nums[i])
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
    // ТЕСТ_1
    ThreadSort alg1("vals1.txt", 13, 5);
    if (!alg1.sort())
        std::cout << "ПРИ РАБОТЕ С ФАЙЛАМИ ПРОИЗОШЛА ОШИБКА" << std::endl;
    else
    {
        std::vector<uint64_t> nums1 = {0, 1, 2, 3, 4, 5, 8, 12, 12, 32, 45, 67, 322};
        check_result("result.txt", nums1);
    }

    remove("result.txt");

    // ТЕСТ_2
    ThreadSort alg2("vals2.txt", 20, 5);
    if (!alg2.sort())
        std::cout << "ПРИ РАБОТЕ С ФАЙЛАМИ ПРОИЗОШЛА ОШИБКА" << std::endl;
    else
    {
        std::vector<uint64_t> nums2 = {0, 0, 2, 2, 2, 2, 3, 4, 6, 8, 9, 9, 53, 56, 66, 78, 134, 230, 234, 4578};
        check_result("result.txt", nums2);
    }
}