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
    v.size = 0;
    v.capacity = n;
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
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

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

void pushBack(vector *v, int x) {
    extension_Memory_Vector_(v);
    append_(v->data,  &v->size, x);
}

void popBack(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "vector is empty");
        exit(1);
    } else
        deleteByPosSaveOrder_(v->data, &v->size, v->size);
}

int* atVector(vector *v, size_t index) {
    return v->data + index - 1;
}

int* back(vector *v) {
    return v->data + v->size - 1;
}

int* front(vector *v) {
    return v->data;
}