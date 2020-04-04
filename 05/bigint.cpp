#include <iostream>
#include <cstring>
#include <algorithm>
#include "bigint.h"

// конструктор класса для создания объекта через строку
BigInt::BigInt(const char *x)
{
    int begin = 0;
    if (x[0] == '-')
    {
        positive = false;
        begin = 1;
        len = strlen(x) - 1;
    }
    else
    {
        begin = 0;
        len = strlen(x);
    }
    numbers = new char[len+1];
    for (int i=begin; i<len+begin; i++)
        numbers[i-begin] = (char)x[i];
}

// конструктор для создания пустого объекта
// (используется в процессе счета)
BigInt::BigInt()
    : numbers(nullptr), len(0) {}

// конструктор копий
BigInt::BigInt(const BigInt &bint)
    : len(bint.getLen()), positive(bint.isPositive())
{
    numbers = new char[len+1];
    for (int i=0; i<len; i++)
        numbers[i] = bint.numbers[i];
}

// оператор копирования
BigInt &BigInt::operator=(BigInt bint)
{
    if (this == &bint)
        return *this;
    len = bint.getLen();
    positive = bint.isPositive();
    char *new_numbers = new char[bint.getLen()+1];
    delete [] numbers;
    numbers = new_numbers;
    for (size_t i=0; i<len; i++)
        numbers[i] = bint.numbers[i];  
}

// функция, заполняющая пустой объект
// (используется в процессе счета)
void BigInt::fill(char *mass, size_t l, bool pos)
{
    positive = pos;
    numbers = new char[l+1];
    len = l;
    for (int i=0; i<l; i++)
        numbers[i] = mass[i];
}

// деструктор
BigInt::~BigInt()
{
    delete [] numbers;
}

// взятие длины числа (количество цифр)
size_t BigInt::getLen() const
{
    return len;
}

// есть ли у числа минус в записи
// (считаем, что для нуля positive = true)
bool BigInt::isPositive() const
{
    return positive;
}

// является ли число нулем
bool BigInt::isZero() const
{
    if ((len == 1) && (numbers[0] == 48))
        return true;
    else
        return false;
}

// для двух чисел равной длины выводит номер инлекса,
// где они впервые отличаются (считаем слева направо)
size_t getFirstNeq(const BigInt &bint_1, const BigInt &bint_2)
{
    if (bint_1.getLen() != bint_2.getLen())
        return -1;

    size_t res;
    for (size_t i=0; i<bint_1.getLen(); i++)
    {
        if (bint_1.numbers[i] != bint_2.numbers[i])
        {
            res = i;
            break;
        }
    }
    return res;
}

// оператор сложения
// анализирует знаки двух чисел и число цифр в них,
// на основе этого вызывает либо метод add, либо sub
// с соответствующим результирующим знаком и с нужным
// порядком слагаемых
BigInt operator+(const BigInt &bint_1, const BigInt &bint_2)
{
    BigInt r;
    if (bint_1.positive && bint_2.positive)
        r = bint_1.add(bint_2, true);
    else if (!bint_1.positive && !bint_2.positive)
        r = bint_1.add(bint_2, false);
    else if (bint_1.positive && !bint_2.positive)
    {
        if (bint_1.getLen() > bint_2.getLen())
            r = bint_1.sub(bint_2, true);
        else if (bint_1.getLen() == bint_2.getLen())
        {
            size_t neq_ind = getFirstNeq(bint_1, bint_2);
            if (bint_1.numbers[neq_ind] >= bint_2.numbers[neq_ind])
                r = bint_1.sub(bint_2, true);
            else
                r = bint_2.sub(bint_1, false);
        }
        else
            r = bint_2.sub(bint_1, false);
    }
    else
    {
        if (bint_1.getLen() > bint_2.getLen())
            r = bint_1.sub(bint_2, false);
        else if (bint_1.getLen() == bint_2.getLen())
        {
            size_t neq_ind = getFirstNeq(bint_1, bint_2);
            if (bint_1.numbers[neq_ind] >= bint_2.numbers[neq_ind])
                r = bint_1.sub(bint_2, false);
            else
                r = bint_2.sub(bint_1, true);
        }
        else
            r = bint_2.sub(bint_1, true);
    }

    return r;
}

// оператор вычитания
// анализирует знаки двух чисел и число цифр в них,
// на основе этого вызывает либо метод add, либо sub
// с соответствующим результирующим знаком и с нужным
// порядком слагаемых
BigInt operator-(const BigInt &bint_1, const BigInt &bint_2)
{
    BigInt r;
    if (bint_1.isPositive() && !bint_2.isPositive())
        r = bint_1.add(bint_2, true);
    else if (!bint_1.isPositive() && bint_2.isPositive())
        r = bint_1.add(bint_2, false);
    else if (bint_1.isPositive() && bint_2.isPositive())
    {
        if (bint_1.getLen() > bint_2.getLen())
            r = bint_1.sub(bint_2, true);
        else if (bint_1.getLen() == bint_2.getLen())
        {
            size_t neq_ind = getFirstNeq(bint_1, bint_2);
            if (bint_1.numbers[neq_ind] >= bint_2.numbers[neq_ind])
                r = bint_1.sub(bint_2, true);
            else
                r = bint_2.sub(bint_1, false);
        }
        else
            r = bint_2.sub(bint_1, false);
    }
    else
    {
        if (bint_1.getLen() > bint_2.getLen())
            r = bint_1.sub(bint_2, false);
        else if (bint_1.getLen() == bint_2.getLen())
        {
            size_t neq_ind = getFirstNeq(bint_1, bint_2);
            if (bint_1.numbers[neq_ind] >= bint_2.numbers[neq_ind])
                r = bint_1.sub(bint_2, false);
            else
                r = bint_2.sub(bint_1, true);
        }
        else
            r = bint_2.sub(bint_1, true);
    }

    return r;
}

// унарный минус
BigInt BigInt::operator-()
{
    BigInt r = *this;
    r.positive = !positive;
    return r;
}

// функция, реализующая сложение двух чисел
// анализирует длины слагаемых, заполянет лишнее нулями
// и складывает
BigInt BigInt::add(const BigInt &bint, bool pos) const
{
    size_t len_1 = len;
    size_t len_2 = bint.getLen();
    size_t len_result = std::max(len_1, len_2) + 1;
    char *num_1 = new char[len_result+1];
    char *num_2 = new char[len_result+1];
    char *result = new char[len_result+1];
    num_1[0] = 48;
    num_2[0] = 48;

    if (len_1 > len_2)
    {
        size_t diff = len_1 - len_2;

        for (int i=0; i<diff; i++)
            num_2[i+1] = 48;

        for (int i=0; i<len_2; i++)
            num_2[i+1+diff] = bint.numbers[i];

        for (int i=0; i<len_1; i++)
            num_1[i+1] = numbers[i];
    }

    if (len_2 >= len_1)
    {
        size_t diff = len_2 - len_1;

        for (int i=0; i<diff;i++)
            num_2[i+1] = 48;

        for (int i=0; i<len_1; i++)
            num_2[i+1+diff] = numbers[i];

        for (int i=0; i<len_2; i++)
            num_1[i+1] = bint.numbers[i];
    }
    
    int curr_memory = 0;
    int prev_memory = 0;
    int curr_num = 0;
    int i_num_1;
    int i_num_2;

    for (int i=len_result-1; i >= 0; i--)
    {
        i_num_1 = int(num_1[i]);
        i_num_2 = int(num_2[i]);
        if (i_num_1 == 0) i_num_1 = 48;
        if (i_num_2 == 0) i_num_2 = 48;
        curr_num = i_num_1-48 + i_num_2-48;
        if (curr_num > 9)
        {
            curr_memory = (int)curr_num / 10;
            curr_num = curr_num % 10;            
        }
        result[i] = (char)(curr_num + prev_memory) + 48;
        prev_memory = curr_memory;
        curr_memory = 0;
    }
   
    BigInt rs;
    
    // проверяем наличие нуля в начале и отбрасываем его
    // если он есть
    if (result[0] == 48)
    {
        char *cut_result = new char[len_result];
        for (int i=0; i<len_result-1; i++)
            cut_result[i] = result[i+1];
        rs.fill(cut_result, len_result-1, pos);
        delete [] cut_result;
        
    }
    else
        rs.fill(result, len_result, pos);

    delete [] num_1;
    delete [] num_2;
    delete [] result;

    return rs;
}

// функция реализующая вычитание двух чисел, первое
// из которых больше (проверка идет в операторе вычитания)
BigInt BigInt::sub(const BigInt &bint, bool pos) const
{
    size_t len_1 = len;
    size_t len_2 = bint.getLen();
    size_t len_result = std::max(len_1, len_2);
    char *num_1 = new char[len_result+1];
    char *num_2 = new char[len_result+1];
    char *result = new char[len_result+1];

    size_t diff = len_1 - len_2;

    for (int i=0; i<diff; i++)
        num_2[i] = 48;

    for (int i=0; i<len_2; i++)
        num_2[i+diff] = bint.numbers[i];

    for (int i=0; i<len_1; i++)
        num_1[i] = numbers[i];

    int curr_digit = 0;
    int digit_1;
    int digit_2;
    int i_num_1;
    int i_num_2;

    for (int i=len_result-1; i >= 0; i--)
    {
        i_num_1 = int(num_1[i]);
        i_num_2 = int(num_2[i]);
        if (i_num_1 == 0) i_num_1 = 48;
        if (i_num_2 == 0) i_num_2 = 48;
        digit_1 = i_num_1 - 48;
        digit_2 = i_num_2 - 48;
        curr_digit = digit_1 - digit_2;
        if (digit_1 < digit_2)
        {
            for (int j=1; j<=i; j++)
            {
                if (num_1[i-j] > 0)
                {
                    num_1[i-j] -= 1;
                    break;
                }
            }
            curr_digit += 10;
        }
        result[i] = (char)(curr_digit) + 48;
    }
    
    BigInt rs;

    // отбрасываем нули в начале, если они есть
    size_t num_zeros = 0;
    for (size_t i=0; i<len_result; i++)
    {
        if (result[i] != 48) break;
        num_zeros += 1;
    }

    if (num_zeros != 0)
    {
        char *new_result = new char[len_result-num_zeros+1];
        for (size_t i=0; i<len_result - num_zeros; i++)
            new_result[i] = result[num_zeros + i];
        rs.fill(new_result, len_result - num_zeros, pos);
        delete [] new_result;
    }
    else
        rs.fill(result, len_result, pos);

    delete [] num_1;
    delete [] num_2;
    delete [] result;

    return rs;
}

// операторы сравнения

bool BigInt::operator<(const BigInt &bint) const
{
    BigInt r = *this - bint;
    if (r.isZero())
        return false;
    return !r.isPositive();
}

bool BigInt::operator>(const BigInt &bint) const
{
    return !this->operator<(bint);
}

bool BigInt::operator<=(const BigInt &bint) const
{
    BigInt r = *this - bint;
    return !r.isPositive();
}

bool BigInt::operator>=(const BigInt &bint) const
{
    return !this->operator<=(bint);
}

// оператор вывода числа в поток
std::ostream &operator<<(std::ostream &stream, const BigInt &bint)
{
    size_t l = bint.getLen();
    bool pos = bint.isPositive();
    if (!pos) stream << '-';
    for (int i=0; i<l; i++)
        stream << bint.numbers[i];
    return stream;    
}
