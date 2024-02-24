#ifndef INC_VECTOR_VOID_H
#define INC_VECTOR_VOID_H

#include <stdint.h>
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <limits.h>
#include "../../algorithms/array/array.c"

typedef struct vector_void {
    void *data; // указатель на нулевой элемент вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
    size_t baseTypeSize; // размер базового типа:
// например, если вектор хранит int -
// то поле baseTypeSize = sizeof(int)
// если вектор хранит float -
// то поле baseTypeSize = sizeof(float)
} vector_void;


//возвращает структуру-дескриптор вектор из n значений.
vector_void createVectorV(size_t n, size_t baseTypeSize);

//изменяет количество
//памяти, выделенное под хранение элементов вектора.
void reserveV(vector_void *v, size_t newCapacity);

//удаляет элементы из контейнера, но не освобождает выделенную память
void clearV(vector_void *v);

//освобождает память, выделенную под
//неиспользуемые элементы.
void shrinkToFitV(vector_void *v);

//освобождает память, выделенную вектору.
void deleteVectorV(vector_void *v);

//проверка на то, является ли вектор пустым
bool isEmptyV(vector_void *v);

//проверка на то, является ли вектор полным
bool isFullV(vector_void *v);

// записывает по адресу destination index-ый элемент вектора v
void getVectorValueV(vector_void *v, size_t index, void* destination);

//записывает на index-ый элемент вектора v значение, расположенное по
//адресу source
void setVectorValueV(vector_void *v, size_t index, void* source);

//добавляет элемент в конец вектора
void pushBackV(vector_void *v, void* source);

//удаляет элемент с конца вектора
void popBackV(vector_void *v);

# endif