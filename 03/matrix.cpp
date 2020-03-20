#include "matrix.h"

// конструктор класса Matrix:
// инициализация числа строк и столбцов, затем
// создается массив указателей на объекты Rows,
// каждый из которых создается с параметром
// columns - длина каждой строки
Matrix::Matrix(int rows, int columns)
    : rows(rows), columns(columns)
{
    massRows = new Rows*[rows];
    for (int i=0; i<rows; i++)
    {
        massRows[i] = new Rows(columns);
    }
}

// конструктор копий класса Matrix
Matrix::Matrix(const Matrix &obj)
    : rows(obj.getRows()), columns(obj.getColumns())
{
    massRows = new Rows*[rows];
    for (int i=0; i<rows; i++)
    {
        massRows[i] = new Rows(columns);
    }
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<columns; j++)
        {
            (*massRows[i])[j] = obj[i][j];
        }
    }
}

// конструктор класса Rows
Matrix::Rows::Rows(int columns)
{
    len = columns;
    mass = new int[len];
}

// деструктор Matrix:
// освобождение памяти для каждого элемента типа Rows,
// освобождение памяти самого объекта Matrix
Matrix::~Matrix()
{
    for (int i=0; i<rows; i++)
    {
        delete massRows[i];
    }
    delete [] massRows;
}

// переопределение оператора *=
void Matrix::operator*=(int num)
{
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<columns; j++)
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

    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<columns; j++)
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
        
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<columns; j++)
        {
            if ((*massRows[i])[j] != matrix[i][j])
                return true;
        }
    }
    return false;
}