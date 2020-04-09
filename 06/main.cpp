#include <iostream>
#include <cassert>
#include "format.h"

// выводим на экран номер теста
void printTest()
{
    static int testNum = 0;
    testNum += 1;
    std::cout << "------" << std::endl;
    std::cout << "ТЕСТ " << testNum << std::endl;
    std::cout << "------" << std::endl;
} 

int main()
{
    std::string string;
    
    // ТЕСТ_1
    printTest();
    string = format("This {1} test {0}.", 1, "is");
    std::cout << string << std::endl;
    assert(string == "This is test 1.");

    // ТЕСТ_2
    printTest();
    string = format("{0} multiplied by {1} is {2}.", 3.1, -2, -6.2);
    std::cout << string << std::endl;
    assert(string == "3.1 multiplied by -2 is -6.2.");

    // ТЕСТ_3
    printTest();
    string = format("Test with empty {}.", '1');
    std::cout << string << std::endl;
    assert(string == "Test with empty .");

    // ТЕСТ_4
    printTest();
    string = format("This is a {0}.", std::string("string"));
    std::cout << string << std::endl;
    assert(string == "This is a string.");

    // ТЕСТ_5
    printTest();
    std::string error;
    try
    {
        string = format("Oops {q}!", 1);
    }
    catch(std::runtime_error er)
    {
        error = er.what();
        std::cout << error << std::endl;
    }
    assert(error == "Not number inside!");

    // ТЕСТ_5
    printTest();
    try
    {
        string = format("Not enough {3}.", 5);
    }
    catch(std::runtime_error er)
    {
        error = er.what();
        std::cout << error << std::endl;
    }
    assert(error == "Not enough arguments!");
}
