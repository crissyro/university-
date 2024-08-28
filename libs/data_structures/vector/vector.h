#ifndef INC_VECTOR_H
#define INC_VECTOR_H

#include <stdint.h>
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "../../algorithms/array/array.c"

typedef struct vector {
    int *data; // указатель на элементы вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
} vector;


//возвращает структуру-дескриптор вектор из n значений.
extern vector createVector(size_t n);

//изменяет количество
//памяти, выделенное под хранение элементов вектора.
extern void reserve(vector *v, size_t newCapacity);

//удаляет элементы из контейнера, но не освобождает выделенную память
extern void clear(vector *v);

//освобождает память, выделенную под
//неиспользуемые элементы.
extern void shrinkToFit(vector *v);

//освобождает память, выделенную вектору.
extern void deleteVector(vector *v);

//проверка на то, является ли вектор пустым
extern bool isEmpty(vector *v);

//проверка на то, является ли вектор полным
extern bool isFull(vector *v);

//возвращает i-ый элемент вектора v
extern int getVectorValue(vector *v, size_t i);

//добавляет элемент в конец вектора
extern void pushBack(vector *v, int x);

//удаляет элемент с конца вектора
extern void popBack(vector *v);

// возвращает указатель на
//index-ый элемент вектора.
extern int* atVector(vector *v, size_t index);

//возвращает указатель на последний элемент вектора.
extern int* back(vector *v);

//возвращает указатель на нулевой элемент вектора.
extern int* front(vector *v);

# endif
