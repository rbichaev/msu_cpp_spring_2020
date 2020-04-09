#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

// функция process распаковывает неизвестное число аргументов
// неизвестных типов и записывает их в поток stream
template <class T>
void process(std::stringstream &stream, const T val)
{
    stream << val;
}

template <class T, class ...Args>
void process(std::stringstream &stream, const T val, const Args ...args)
{
    stream << val << " ";
    process(stream, args...);
}

// функция format принимает на вход строку, которую нужно
// отформатировать, с включенными зарезервированными символами
// скобок {}, внутри которых индексы аргументов, которые
// подаются после строки
template <class ...Args>
std::string format(const char *text, const Args ...args)
{
    // создаем и заполняем поток
    std::stringstream stream;
    process(stream, args...);
    // разделяем строку, содержащуюся в потоке, пробелами:
    // с помощью итератора проходим по потоку и заполняем
    // вектор найденными значениями
    std::istream_iterator<std::string> beg(stream), end;
    std::vector<std::string> params(beg, end);
    size_t len = params.size();
    std::string result = "";
    bool write = true;
    
    // проходим по поданной в функцию строке и заполняем
    // выходную строку
    for (int i=0; text[i]; i++)
    {
        if (text[i] == '{')
        {
            write = false;
            std::string str_number = "";
            int j = i + 1;
            while(text[j] != '}')
            {
                str_number += text[j];
                j++;
            }
            if (str_number != "")
            {
                if (!std::all_of(str_number.begin(), str_number.end(), isdigit))
                    throw std::runtime_error("Not number inside!");
                int number = std::stoi(str_number);
                if (number >= len)
                    throw std::runtime_error("Not enough arguments!");
                else
                    result += params[number];
            }
        }
        if (write == true) result += text[i];
        if (text[i] == '}') write = true;
    }
    return result;
}
