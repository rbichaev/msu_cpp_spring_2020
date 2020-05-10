#include <iostream>
#include <string>
#include "threadsort.h"

int main()
{
    ThreadSort alg("proba.txt", 13, 5);
    if (!alg.sort())
        std::cout << "ПРИ РАБОТЕ С ФАЙЛАМИ ПРОИЗОШЛА ОШИБКА" << std::endl;

    uint64_t nums[] = {0, 1, 2, 3, 4, 5, 8, 12, 12, 32, 45, 67, 322};

    std::ifstream stream;
    std::string str;

    bool mistake = false;

    stream.open("result.txt");
    for (size_t i=0; i<13; i++)
    {
        getline(stream, str);
        if (std::stoi(str) != nums[i])
        {
            std::cout << "WRONG!" << std::endl;
            break;
        }
    }

    if (!mistake)
        std::cout << "Well done!" << std::endl;

    stream.close();
}