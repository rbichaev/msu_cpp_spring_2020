#include <iostream>

// класс матрица(Matrix) - состоит из массива 
// указателей на объекты класса строк(Rows)
class Matrix
{
    int rows;
    int columns;

public:

    class Rows
    {
        int len;
    public:
        int *mass;
        Rows(int columns);
        ~Rows() { delete [] mass; }
        int &operator[](int i) const { return mass[i]; };
        int getLen() const { return len; }
    };

    Rows **massRows;

    Matrix(int rows, int columns);
    Matrix(const Matrix &obj);
    ~Matrix();
    Rows &operator[](int row) const { return *massRows[row]; };
    void operator*=(int num);
    bool operator==(const Matrix &matrix) const;
    bool operator!=(const Matrix &matrix) const;
    int getRows() const { return rows; } 
    int getColumns() const { return columns; };
};