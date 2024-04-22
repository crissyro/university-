#ifndef INC_MATRIX_H
#define INC_MATRIX_H

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>


typedef struct matrix {
    int **values; // элементы матрицы
    int nRows; // количество рядов
    int nCols; // количество столбцов
} matrix;

typedef struct position {
    int rowIndex;
    int colIndex;
} position;

//размещает в динамической памяти матрицу размером nRows на nCols
matrix getMemMatrix(int nRows, int nCols) ;

//размещает в динамической памяти массив из nMatrices матриц размером nRows на nCols
matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) ;

//освобождает память, выделенную под хранение матрицы m
void freeMemMatrix(matrix *m) ;

//освобождает память, выделенную под хранение массива ms из nMatrices матриц
void freeMemMatrices(matrix *ms, int nMatrices) ;

//ввод матрицы m
void inputMatrix(matrix *m) ;

//ввод массива из nMatrices матриц, хранящейся по адресу ms
void inputMatrices(matrix *ms, int nMatrices) ;

//вывод матрицы m
void outputMatrix(matrix m) ;

//вывод массива из nMatrices матриц, хранящейся по адресу ms
void outputMatrices(matrix *ms, int nMatrices) ;

//обмен строк с порядковыми номерами i1 и i2 в матрице m.
void swapRows(matrix m, int i1, int i2) ;

//обмен колонок с порядковыми номерами j1 и j2 в матрице m
void swapColumns(matrix m, int j1, int j2) ;

//выполняет сортировку вставками строк матрицы m
//по неубыванию значения функции criteria применяемой для строк
void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)) ;

//выполняет сортировку выбором столбцов матрицы m
// по неубыванию значения функции criteria применяемой для столбцов
void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int)) ;

//возвращает значение ’истина’, если
//матрица m является квадратной, ложь – в противном случае
bool isSquareMatrix(matrix *m) ;

//возвращает значение ’истина’,
//если матрицы m1 и m2 равны, ложь – в противном случае
bool areTwoMatricesEqual(matrix *m1, matrix *m2) ;

// возвращает значение ’истина’, если матрица
//m является единичной, ложь – в противном случае
bool isEMatrix(matrix *m) ;

//возвращает значение ’истина’,
//если матрица m является симметричной, ложь – в противном случае
bool isSymmetricMatrix(matrix *m) ;

//транспонирует квадратную матрицу m
void transposeSquareMatrix(matrix *m)  ;

//транспонирует матрицу m
void transposeMatrix(matrix *m) ;

//возвращает позицию минимального элемента матрицы m
position getMinValuePos(matrix m) ;

//возвращает позицию максимального элемента матрицы m
position getMaxValuePos(matrix m) ;

//возвращает матрицу размера nRows на nCols, построенную из элементов массива a
matrix createMatrixFromArray(const int *a, int nRows, int nCols) ;

//возвращает указатель на нулевую матрицу массива из nMatrices матриц,
//размещенных в динамической памяти, построенных из элементов массива a
matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) ;

matrix copyMatrix(matrix *original);

#endif