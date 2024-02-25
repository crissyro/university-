#include "vector_void.h"


void check_MemoryV_(vector_void *v) {
    if (v->data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

void appendV_(void* *const a, size_t * n, void* value) {
    a[*n] = value;
    (*n)++;
}

void extension_Memory_VectorV_(vector_void *v) {
    if (v->capacity == 0) {
        v->data = (void*)realloc(v->data, v->baseTypeSize);
        v->capacity = 1;
    } else if (isFullV(v)){
        v->data = (void*)realloc(v->data, v->baseTypeSize * v->capacity * 2);
        v->capacity *= 2;
    }
    check_MemoryV_(v);
}


vector_void createVectorV(size_t n, size_t baseTypeSize) {
    vector_void v;
    v.size = 0;
    v.capacity = n;
    v.baseTypeSize = sizeof (baseTypeSize);
    v.data = (void*)malloc(v.capacity * v.baseTypeSize);
}

void reserveV(vector_void *v, size_t newCapacity) {
    if (newCapacity == 0)
        v->data = NULL;
    else if (newCapacity < v->size) {
        v->size = newCapacity;
        v->capacity = newCapacity;
        v->data = (void*)realloc(v->data, v->baseTypeSize*v->size);
    } else {
        v->capacity = newCapacity;
        v->data = (void*) realloc(v->data, v->baseTypeSize * v->capacity);
    }
}

void clearV(vector_void *v) {
    v->size = 0;
}

void shrinkToFitV(vector_void *v) {
    if (!isFullV(v)) {
        v->data = (void*)realloc(v->data, v->baseTypeSize *v->size);
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
    char *source = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

void setVectorValueV(vector_void *v, size_t index, void *source) {
    char *destination = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

void pushBackV(vector_void *v, void* source) {
    if (v->size >= v->capacity) {
        size_t curr_size = v->size == 0 ? 1 : v->size * 2;
        reserveV(v, curr_size);
    }
    void* dest = (void*) v->data + v->size * v->baseTypeSize;
    memcpy(dest, source, v->baseTypeSize);
    v->size++;
}

void popBackV(vector_void *v) {
    if (isEmptyV(v)) {
        fprintf(stderr, "vector is empty");
        exit(1);
    } else
        deleteByPosSaveOrder_(v->data, &v->size, v->size);
}