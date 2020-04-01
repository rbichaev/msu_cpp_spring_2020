#include <iostream>
#include <algorithm>

enum Error
{
    NoError,
    CorruptedArchive
};


// сериализатор
class Serializer
{
    std::ofstream &streamSer;
    const char sep = ' ';

public:

    Serializer(std::ofstream &stream)
        : streamSer(stream) {}

    ~Serializer() { streamSer.close(); }


    // вызывается явно в функции main для начала записи
    template <class Object>
    Error save(Object &object) { return object.doSth(*this); }


    // реализация раскрутки аргументов
    template<class T, class ...Args>
    Error process(T &val, Args &...args)
    {
        if (print(val) == Error::NoError)
            return process(args...);
        else
            return Error::CorruptedArchive;
    }

    template<class T>
    Error process(T &val)
    {
        return print(val);
    }


    // используется для реализации интерфейса функции, указанной в структуре Data,
    // переменные которой подлежат записи
    template <class ...Args>
    Error operator()(Args &...args) { return process(args...); }
    

    // запись в файл
    template <class T>
    Error print(T &val)
    {
        streamSer << std::boolalpha << val << sep;
        streamSer << std::noboolalpha;
        return Error::NoError;
    }
};



// десериализатор
class Deserializer
{
    std::ifstream &streamDes;
    const char sep = ' ';

public:

    Deserializer(std::ifstream &stream)
        : streamDes(stream) {}

    ~Deserializer()
    {
        streamDes.close();
    }

    // вызывается явно в функции main для начала чтения 
    template <class Object>
    Error load(Object &object) 
	{
        return object.doSth(*this);
	}
    

    // реализация раскрутки аргументов
    template<class T, class ...Args>
    Error process(T &val, Args &...args)
    {
        if (read(val) == Error::NoError)
            return process(args...);
        else
            return Error::CorruptedArchive;
    }

    template<class T>
    Error process(T &val)
    {
        return read(val); 
    }
    

    // используется для реализации интерфейса функции, указанной в структуре Data,
    // переменные которой подлежат изменению
    template <class ...Args>
    Error operator()(Args &...args) 
    {
        return process(args...);
    }


    // один аргумент - число 
    Error read(uint64_t &val)
    {
        std::string text;
        streamDes >> text;
        
        // проверяем, является ли прочитанное числом
        if (std::all_of(text.begin(), text.end(), isdigit))
        {                   
            int64_t v = std::stoi(text);
            val = v;
            return Error::NoError;
        }
        else
            return Error::CorruptedArchive;
    }

    // один аргумент типа bool
    Error read(bool &val)
    {
        std::string text;
        streamDes >> text;

        // проверяем, является ли прочитанное bool'ом
        if (text == "true")
        {
            val = true;
            return Error::NoError;
        }
        else if (text == "false")
        {
            val = false;
            return Error::NoError;
        }
        else
            return Error::CorruptedArchive;
    }
};
