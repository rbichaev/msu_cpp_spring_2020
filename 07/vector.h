#include <iostream>
#include <iterator>

// класс итератор
template <class T>
class Iterator
    : public std::iterator<std::forward_iterator_tag, T>
{
    T *ptr_;
public:
    Iterator(T *ptr)
        : ptr_(ptr) {}
    
    bool operator==(const Iterator<T> &other) const
    {
        return ptr_ == other.ptr_;
    }

    bool operator!=(const Iterator<T> &other) const
    {
        return !(*this == other);
    }

    T &operator*() const
    {
        return *ptr_;
    }

    Iterator &operator+(size_t i)
    {
        ptr_ += i;
        return *this;
    }

    Iterator &operator++()
    {
        ++ptr_;
        return *this;
    }
};

// класс вектор
template<class T, class Alloc = std::allocator<T>>
class vector
{
    using size_type = size_t;
    using value_type = T;
    using vt_pointer = T*;
    using reference = T&;
    using const_reference = const T&;
	using allocator_type = Alloc;
    using iterator = Iterator<T>;
    using const_iterator = const Iterator<T>;
    using reverse_iterator = std::reverse_iterator<Iterator<T>>;

    size_type size_;
    value_type *pointer;
    allocator_type alloc;

public:
    
    // конструкторы
    vector(size_type count)
        : size_(count), pointer(alloc.allocate(count)) {};

    vector(size_type count, const value_type &defaultValue)
        : size_(count), pointer(alloc.allocate(count))
    {
        for (size_type i=0; i<count; i++)
            pointer[i] = defaultValue;
    }

    vector(std::initializer_list<value_type> init)
        : size_(init.size())
    {
        size_type i = 0;
        auto current = init.begin();
        const auto end = init.end();
        pointer = alloc.allocate(end - current);
        while (current != end)
        {
            pointer[i++] = *current++;
        }
    }
    
    // деструктор
    ~vector()
    {
        alloc.deallocate(pointer, size_);
    }
    

    // функционал итераторов
    iterator begin() 
    {
        return iterator(pointer);
    }

    iterator end() 
    {
        return iterator(pointer + size_);
    }

     reverse_iterator rbegin() const
    {
        return reverse_iterator(end());
    }

    reverse_iterator rend() const
    {
        return reverse_iterator(begin());
    }


    // изменение размера
    void resize(size_type newSize)
    {
        vt_pointer new_pointer = alloc.allocate(newSize);
        size_type min_size = size_;

        if (newSize < min_size)
            min_size = newSize;

        for (size_type i=0; i<min_size; i++)
            new_pointer[i] = pointer[i];

        alloc.deallocate(pointer, size_);
        pointer = new_pointer;
        size_ = newSize;
    }

    // изменение размера и дополнение пустых мест поданным значением
    void resize(size_type newSize, const value_type &defaultValue)
    {
        size_type old_size = size_;
        resize(newSize);
        if (newSize > old_size)
        {
            for (size_type i=old_size; i<newSize; i++)
                pointer[i] = defaultValue;
        }
    }

    // вставка элемента в конец вектора
    void push_back(const value_type &value)
    {
        if (size_ == 0)
        {
            pointer = alloc.allocate(1);
            pointer[0] = value;
        }
        else
            resize(size_ + 1, value);
    }

    // вывод размера вектора
    size_type size() const
    {
        return size_;
    }

    // вектор пуст?
    bool empty() const
    {
        if (size_ == 0)
            return true;
        else
            return false;
    }

    // удаление последнего элемента вектора
    void pop_back()
    {
        if (size_ == 0)
            throw -1;

        resize(size_ - 1);
    }

    // оператор []
    reference operator[](size_type pos) const
    {
        return pointer[pos];
    }

    // выделяет память - гарантирует
    //  по крайней мере поданный размер
    void reserve(size_type count)
    {
        if (count <= size_)
            return;
                
        vt_pointer new_pointer = alloc.allocate(count);

        for (size_type i=0; i<size_; i++)
            new_pointer[i] = pointer[i];

        alloc.deallocate(pointer, size_);
        pointer = new_pointer;
        size_ = count;
    }

    // удаление элемента в заданном итератором месте
    iterator erase(const_iterator where) 
    {
        vt_pointer new_pointer = alloc.allocate(size_-1);
        size_type shift = 0;
        for (size_type i=0; i<size_; i++)
        {
            if (&pointer[i] == &(*where))
            {
                shift = 1;
                continue;
            }
            new_pointer[i - shift] = pointer[i];
        }
        alloc.deallocate(pointer, size_);
        pointer = new_pointer;
        size_ = size_ - 1;
    }

    // удаление элементов в поданном диапазоне
    // итераторов в формате [from, to)
    iterator erase(const_iterator from, const_iterator to)
    {
        vt_pointer new_pointer = alloc.allocate(size_ - (&(*to)-&(*from)));
        size_type shift = 0;

        for (size_type i=0; i<size_; i++)
        {
            if ((&pointer[i] >= &(*from)) && (&pointer[i] < &(*to)))
            {
                shift += 1;
                continue;
            }
            new_pointer[i - shift] = pointer[i];
        }

        alloc.deallocate(pointer, size_);
        pointer = new_pointer;
        size_ = size_ - (&(*to) - &(*from));
    }

    // очистка вектора
    void clear()
    {
        alloc.deallocate(pointer, size_);
        pointer = nullptr;
        size_ = 0;
    }

