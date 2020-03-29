#include <iostream>
#include <algorithm>

enum Error
{
    NoError,
    CorruptedArchive
};

// функции для проверки типа аргумента и выбора нужного шаблона
// подобные есть в std, но я реализовал эти, чтобы
// посмотреть, как они работают
namespace mns {
    
    template <class T>
    struct isbool
    {
        static constexpr bool value = false;
    };

    template <>
    struct isbool<bool>
    {
        static constexpr bool value = true;
    };

    template <bool, class T = void>
    struct enableif 
    {
    };

    template <class T>
    struct enableif<true, T>
    {
        using type = T;
    };
}

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
    Error save(Object &object) const { return object.doSth(*this); }

    // используется для реализации интерфейса функции, указанной в структуре Data,
    // переменные которой подлежат записи
    template <class ...Args>
    Error operator()(const Args &...args) const { return print(args...); }


    // функции, реализующие запись переменных; 
    // вызов каждой зависит от количества аргументов

    // несколько аргументов
    template <class T, class ...Args>
    Error print(const T val, const Args ...args) const
    {
        streamSer << std::boolalpha << val << sep;
        streamSer << std::noboolalpha;
        return print(args...);
    }

    // один аргумент
    template <class T>
    Error print(const T val) const
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

    // используется для реализации интерфейса функции, указанной в структуре Data,
    // переменные которой подлежат изменению
    template <class ...Args>
    Error operator()(Args &...args) 
    {
        return read(args...);
    }


    // функции, реализующие чтение, в зависимости от числа аргументов (Args и args)
    // и от типов параметров (тут используются функции из namespace mns)

    // несколько аргументов, первый типа bool
    template <class T, class ...Args, typename mns::enableif<mns::isbool<T>::value>::type * = nullptr>
    Error read(T &val, Args &...args)
    {
        std::string text;
        streamDes >> text;

        if (text == "true")
            val = true;
        else if (text == "false")
            val = false;
        else
            return Error::CorruptedArchive;

        return read(args...);
    }

    // несколько аргументов, первый тип НЕ bool
    template <class T, class ...Args, typename mns::enableif<!mns::isbool<T>::value>::type * = nullptr>
    Error read(T &val, Args &...args)
    {
        std::string text;
        streamDes >> text;
        if (std::all_of(text.begin(), text.end(), isdigit))
        {                   
            int64_t v = std::stoi(text);
            val = v;
            return read(args...);
        }
        else
            return Error::CorruptedArchive;
    }

    // один аргумент типа bool
    template <class T, typename mns::enableif<mns::isbool<T>::value>::type * = nullptr>
    Error read(T &val)
    {
        std::string text;
        streamDes >> text;

        // проверяем, является ли значение bool
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

    // один аргумент - число 
    template <class T, typename mns::enableif<!mns::isbool<T>::value>::type * = nullptr>
    Error read(T &val)
    {
        std::string text;
        streamDes >> text;
        
        // проверяем, что это число
        if (std::all_of(text.begin(), text.end(), isdigit))
        {                   
            int64_t v = std::stoi(text);
            val = v;
            return Error::NoError;
        }
        else
            return Error::CorruptedArchive;
    }
};
