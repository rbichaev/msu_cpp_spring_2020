#include <iostream>
#include <fstream>
#include <assert.h>
#include "ser_des.h"

// структура для тестирования
struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

	// функция, которая вызывается при
	// записи(Method = Serializator) / чтении(Method = Deserializator)
	template <class Method>
    Error doSth(Method &method)
    {
        return method(a, b, c);
    }
};

// структура с другим набором типов атрибутов
struct DataAlter
{
    bool a;
    bool b;
    uint64_t c;

	// функция, которая вызывается при
	// записи(Method = Serializator) / чтении(Method = Deserializator)
	template <class Method>
    Error doSth(Method &method)
    {
        return method(a, b, c);
    }
};

// выводим на экран номер теста
void printTest()
{
    static int testNum = 0;
    testNum += 1;
    std::cout << "------" << std::endl;
    std::cout << "ТЕСТ " << testNum << std::endl;
    std::cout << "------" << std::endl;
}

// тест 1
// записываем данные, затем считываем их в структуру того же типа
// тест пройден, если данные совпали и не было ошибок
void test1()
{
	printTest();

	// создаем структуру и записываем данные о ней в файл
	Data x{133, true, 2};

	std::ofstream ostream("file.txt");

	Serializer serializer(ostream);
	serializer.save(x);

	ostream.close();

	// создаем новую структуру и заполняем ее данными из файла
	Data y{0, false, 0};

	std::ifstream istream("file.txt");

	Deserializer deserializer(istream);
	Error err = deserializer.load(y);

	istream.close();

	// проверяем отсутствие ошибки и равенство данных
	if ( (err == Error::NoError) && (x.a == y.a) && (x.b == y.b) && (x.c == y.c) )
		std::cout << "Тест пройден!" << std::endl;
	else
		std::cout << "Ошибка!" << std::endl;
}

// тест 2
// записываем данные, затем считываем их в структуру другого типа
// тест пройден, если была ошибка Error::CorruptedArchive
void test2()
{
	printTest();

	// создаем структуру и записываем данные о ней в файл
	Data x{133, true, 2};

	std::ofstream ostream("file.txt");

	Serializer serializer(ostream);
	serializer.save(x);

	ostream.close();

	// создаем новую структуру и пробуем заполнить ее данными из файла
	DataAlter y{false, false, 0};

	std::ifstream istream("file.txt");

	Deserializer deserializer(istream);
	Error err = deserializer.load(y);

	istream.close();

	// проверяем наличие ошибки
	if (err == Error::CorruptedArchive)
		std::cout << "Тест пройден!" << std::endl;
	else
		std::cout << "Ошибка!" << std::endl;
}

int main()
{
	test1();
	test2();
}
