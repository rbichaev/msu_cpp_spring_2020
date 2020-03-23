#include <iostream>

// класс матрица(Matrix) - состоит из массива 
// указателей на объекты класса строк(Rows)
class Matrix
{
    size_t rows;
    size_t columns;

public:

    class Rows
    {
        size_t len;
    public:
        int *mass;
        Rows(size_t columns);
        ~Rows() { delete [] mass; }
        int &operator[](int i) { return mass[i]; };
        const int &operator[](int i) const { return mass[i]; };
        size_t getLen() const { return len; }
    };

    Rows **massRows;

    Matrix(size_t rows, size_t columns);
    Matrix(const Matrix &obj);
    ~Matrix();
    Rows &operator[](size_t row) { return *massRows[row]; };
    const Rows &operator[](size_t row) const { return *massRows[row]; };
    void operator*=(int num);
    bool operator==(const Matrix &matrix) const;
    bool operator!=(const Matrix &matrix) const;
    size_t getRows() const { return rows; } 
    size_t getColumns() const { return columns; };
};