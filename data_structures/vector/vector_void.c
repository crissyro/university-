#include "vector_void.h"


void check_MemoryV_(vector_void *v) {
    if (v->data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
}

void extension_Memory_VectorV_(vector_void *v) {
    if (v->capacity == 0) {
        v->data = (int*)realloc(v->data, sizeof(int));
        v->capacity = 1;
    } else if (isFullV(v)){
        v->data = (int*)realloc(v->data, sizeof(int)*v->capacity * 2);
        v->capacity *= 2;
    }
    check_MemoryV_(v);
}


vector_void createVectorV(size_t n, size_t baseTypeSize);

void reserveV(vector_void *v, size_t newCapacity);

void clearV(vector_void *v);

void shrinkToFitV(vector_void *v);


void deleteVectorV(vector_void *v);

bool isEmptyV(vector_void *v) {
    return v->size == 0 ? true : false;
}

bool isFullV(vector_void *v) {
    return v->size == v->capacity ? true : false;
}

void getVectorValueV(vector_void *v, size_t index, void *destination);

void setVectorValueV(vector_void *v, size_t index, void *source);

void pushBackV(vector_void *v, void *source);

void popBackV(vector_void *v);