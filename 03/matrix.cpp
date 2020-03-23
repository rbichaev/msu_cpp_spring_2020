#include "matrix.h"

// конструктор класса Matrix:
// инициализация числа строк и столбцов, затем
// создается массив указателей на объекты Rows,
// каждый из которых создается с параметром
// columns - длина каждой строки
Matrix::Matrix(size_t rows, size_t columns)
    : rows(rows), columns(columns)
{
    massRows = new Rows*[rows];
    for (size_t i=0; i<rows; i++)
    {
        massRows[i] = new Rows(columns);
    }
}

// конструктор копий класса Matrix
Matrix::Matrix(const Matrix &obj)
    : rows(obj.getRows()), columns(obj.getColumns())
{
    massRows = new Rows*[rows];
    for (size_t i=0; i<rows; i++)
    {
        massRows[i] = new Rows(columns);
    }
    for (size_t i=0; i<rows; i++)
    {
        for (size_t j=0; j<columns; j++)
        {
            (*massRows[i])[j] = obj[i][j];
        }
    }
}

// конструктор класса Rows
Matrix::Rows::Rows(size_t columns)
{
    len = columns;
    mass = new int[len];
}

// деструктор Matrix:
// освобождение памяти для каждого элемента типа Rows,
// освобождение памяти самого объекта Matrix
Matrix::~Matrix()
{
    for (size_t i=0; i<rows; i++)
    {
        delete massRows[i];
    }
    delete [] massRows;
}

// переопределение оператора *=
void Matrix::operator*=(int num)
{
    for (size_t i=0; i<rows; i++)
    {
        for (size_t j=0; j<columns; j++)
        {
            (*massRows[i])[j] *= num;
        }
    }
}

// переопределение оператора ==
bool Matrix::operator==(const Matrix &matrix) const
{
    if ((rows != matrix.getRows()) || (columns != matrix.getColumns()))
        return false;

    for (size_t i=0; i<rows; i++)
    {
        for (size_t j=0; j<columns; j++)
        {
            if ((*massRows[i])[j] != matrix[i][j])
                return false;
        }
    }
    return true;
}

// переопределение оператора !=
bool Matrix::operator!=(const Matrix &matrix) const
{
    if ((rows != matrix.getRows()) || (columns != matrix.getColumns()))
        return true;
        
    for (size_t i=0; i<rows; i++)
    {
        for (size_t j=0; j<columns; j++)
        {
            if ((*massRows[i])[j] != matrix[i][j])
                return true;
        }
    }
    return false;
}