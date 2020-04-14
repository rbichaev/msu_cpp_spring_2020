#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

// функция fill_vector распаковывает неизвестное число аргументов
// неизвестных типов и записывает их в вектор параметров
template <class T>
void fill_vector(std::vector<std::string> &vec, const T &val)
{
    std::stringstream stream;
    stream << val;
    std::string s;
    stream >> s;
    vec.push_back(s);
}

template <class T, class ...Args>
void fill_vector(std::vector<std::string> &vec, const T &val, const Args &...args)
{
    std::stringstream stream;
    stream << val;
    std::string s;
    stream >> s;
    vec.push_back(s);
    fill_vector(vec, args...);
}

// функция format принимает на вход строку, которую нужно
// отформатировать, с включенными зарезервированными символами
// скобок {}, внутри которых индексы аргументов, которые
// подаются после строки
template <class ...Args>
std::string format(const char *text, const Args &...args)
{
    std::vector<std::string> params;
    fill_vector(params, args...);
    size_t len = params.size();
    std::string result = "";
    bool write = true;
    
    // проходим по поданной в функцию строке и заполняем
    // выходную строку
    for (size_t i=0; text[i]; i++)
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
