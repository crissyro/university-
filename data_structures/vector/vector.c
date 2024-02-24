#include "vector.h"

//– Если ОС не смогла выделить необходимый фрагмент памяти, вывести
//сообщение в поток ошибок и прервать выполнение программы

void check_Memory_(vector *v) {
    if (v->data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

bool isEmpty(vector *v) {
    return v->size == 0 ? true : false;
}

bool isFull(vector *v) {
    return v->size == v->capacity ? true : false;
}


vector createVector(size_t n) {
    vector v;
    v.size = n;
    v.capacity = n * 2;
    v.data = (int *)malloc(v.capacity * sizeof (int));

    check_Memory_(&v);

    return v;
}


void reserve(vector *v, size_t newCapacity) {
    if (newCapacity == 0)
        v->data = NULL;
    else if (newCapacity < v->size) {
        v->size = newCapacity;
        v->capacity = newCapacity;
        v->data = (int*)realloc(v->data, sizeof(int)*v->size);
    } else {
        v->capacity = newCapacity;
        v->data = (int*)realloc(v->data, sizeof(int)*v->capacity);
        check_Memory_(&v);
    }
}

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v) {
    if (!isFull(v)) {
        v->data = (int*)realloc(v->data, sizeof(int)*v->size);
        v->capacity = v->size;
    }
}

void deleteVector(vector *v) {
    free(v -> data);
}


//возвращает i-ый элемент вектора v
int getVectorValue(vector *v, size_t i) {
    return v->data[i];
}

void extension_Memory_Vector_(vector *v) {
    if (v->capacity == 0) {
        v->data = (int*)realloc(v->data, sizeof(int));
        v->capacity = 1;
    } else if (isFull(v)){
        v->data = (int*)realloc(v->data, sizeof(int)*v->capacity * 2);
        v->capacity *= 2;
    }
    check_Memory_(v);
}

//добавляет элемент в конец вектора
void pushBack(vector *v, int x) {
    extension_Memory_Vector_(v);
    append_(v->data,  &v->size, x);
}

//удаляет элемент с конца вектора
void popBack(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "vector is empty");
        exit(1);
    } else
        deleteByPosSaveOrder_(v->data, &v->size, v->size);
}

// возвращает указатель на
//index-ый элемент вектора.
int* atVector(vector *v, size_t index);

//возвращает указатель на последний элемент вектора.
int* back(vector *v);

//возвращает указатель на нулевой элемент вектора.
int* front(vector *v);