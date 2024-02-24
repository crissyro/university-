#include "vector_void.h"


void check_MemoryV_(vector_void *v) {
    if (v->data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

void appendV_(void* *const a, size_t *const n, void *value) {
    a[*n] = value;
    (*n)++;
}

void extension_Memory_VectorV_(vector_void *v) {
    if (v->capacity == 0) {
        v->data = (void*)realloc(v->data, sizeof(void*));
        v->capacity = 1;
    } else if (isFullV(v)){
        v->data = (void*)realloc(v->data, sizeof(void*)*v->capacity * 2);
        v->capacity *= 2;
    }
    check_MemoryV_(v);
}


vector_void createVectorV(size_t n, size_t baseTypeSize) {
    vector_void v;
    v.size = 0;
    v.capacity = n;
    v.baseTypeSize = sizeof (void*);
    v.data = (void*)malloc(v.capacity * sizeof (void*));
}

void reserveV(vector_void *v, size_t newCapacity) {
    if (newCapacity == 0)
        v->data = NULL;
    else if (newCapacity < v->size) {
        v->size = newCapacity;
        v->capacity = newCapacity;
        v->data = (void*)realloc(v->data, sizeof(void*)*v->size);
    } else {
        v->capacity = newCapacity;
        v->data = (void *) realloc(v->data, sizeof(void *) * v->capacity);
    }
}

void clearV(vector_void *v) {
    v->size = 0;
}

void shrinkToFitV(vector_void *v) {
    if (!isFullV(v)) {
        v->data = (void*)realloc(v->data, sizeof(void)*v->size);
        v->capacity = v->size;
    }
}


void deleteVectorV(vector_void *v) {
    free(v -> data);
}

bool isEmptyV(vector_void *v) {
    return v->size == 0 ? true : false;
}

bool isFullV(vector_void *v) {
    return v->size == v->capacity ? true : false;
}

void getVectorValueV(vector_void *v, size_t index, void *destination) {
    return v->data[index];
}

void setVectorValueV(vector_void *v, size_t index, void *source) {

}

void pushBackV(vector_void *v, void* source) {
    extension_Memory_VectorV_(v);
    appendV_(v->data, &v->size, source);
}

void popBackV(vector_void *v) {
    if (isEmptyV(v)) {
        fprintf(stderr, "vector is empty");
        exit(1);
    } else
        deleteByPosSaveOrder_(v->data, &v->size, v->size);
}