#include <iostream>
#include "threadsum.h"

int main()
{
    ThreadSum summator;
    int result = summator.sum_numbers("numbers.txt");
    std::cout << result << std::endl;
    return 0;
}