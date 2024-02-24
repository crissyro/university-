#include "vector.h"

//– Если ОС не смогла выделить необходимый фрагмент памяти, вывести
//сообщение в поток ошибок и прервать выполнение программы

void check_Memory(vector *v) {
    if (v->data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

vector createVector(size_t n) {
    vector v;
    v.size = n;
    v.capacity = n * 2;
    v.data = (int *)malloc(v.capacity * sizeof (int));

    check_Memory(&v);

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
        check_Memory(&v);
    }
}

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v) {
    if (v->size != v->capacity) {
        v->data = (int*)realloc(v->data, sizeof(int)*v->size);
        v->capacity = v->size;
    }
}

void deleteVector(vector *v) {
    free(v -> data);
}