#include <iostream>
#include <iomanip>
#include "matrix.h"

// выводим на экран номер теста
void printTest()
{
    static int testNum = 0;
    testNum += 1;
    std::cout << "------" << std::endl;
    std::cout << "ТЕСТ " << testNum << std::endl;
    std::cout << "------" << std::endl;
}

// выводим на экран матрицу
void printMatrix(const Matrix &matrix)
{
    int rows = matrix.getRows();
    int columns = matrix.getColumns();

    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<columns; j++)
        {
            std::cout << std::setw(6) << matrix[i][j];
        }
        std::cout << std::endl;
    }
}

// проверка равенства двух матриц посредством операторов == и !=
void isEqual(const Matrix &matrix_1, const Matrix &matrix_2)
{    
    std::cout << "Проверка оператора ==:" << std::endl;
    if (matrix_1 == matrix_2)
        std::cout << "  матрицы равны" << std::endl;
    else
        std::cout << "  матрицы неравны" << std::endl;

    std::cout << "Проверка оператора !=:" << std::endl;
    if (matrix_1 != matrix_2)
        std::cout << "  матрицы неравны" << std::endl;
    else
        std::cout << "  матрицы равны" << std::endl;
}

// тест: умножение матрицы на число
void test1(int rows, int columns)
{
    printTest();

    Matrix matrix(rows, columns);
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<columns; j++)
        {
            matrix[i][j] = i - j;
        }
    }
    std::cout << "Матрица имеет вид:" << std::endl;
    printMatrix(matrix);
    matrix *= 5;
    std::cout << "Матрица после умножения на 5 имеет вид:" << std::endl;
    printMatrix(matrix);
}

// тест: проверка равенства матриц
void test2(int rows_1, int columns_1, int rows_2, int columns_2)
{
    printTest();

    Matrix matrix_1(rows_1, columns_1);
    for (int i=0; i<rows_1; i++)
    {
        for (int j=0; j<columns_1; j++)
        {
            matrix_1[i][j] = 2*i - j;
        }
    }

    Matrix matrix_2(rows_2, columns_2);
    for (int i=0; i<rows_2; i++)
    {
        for (int j=0; j<columns_2; j++)
        {
            matrix_2[i][j] = 2*i + 4*j;
        }
    }

    std::cout << "Матрица 1 имеет вид:" << std::endl;
    printMatrix(matrix_1);
    std::cout << "Матрица 2 имеет вид:" << std::endl;
    printMatrix(matrix_2);

    isEqual(matrix_1, matrix_2);
}

// проверка равенства матрицы себе же
void test3(int rows, int columns)
{
    printTest();

    Matrix matrix_1(rows, columns);
    
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<columns; j++)
        {
            matrix_1[i][j] = 2*i - j;
        }
    }
    
    // создадим копию для проверки работы конструктора копий
    Matrix matrix_2 = matrix_1;

    std::cout << "Матрица 1 имеет вид:" << std::endl;
    printMatrix(matrix_1);
    std::cout << "Матрица 2 имеет вид:" << std::endl;
    printMatrix(matrix_2);

    isEqual(matrix_1, matrix_2);
}

int main()
{
    test1(4, 3);
    test2(4, 3, 5, 4);
    test2(3, 4, 3, 4);
    test3(5, 3);
}