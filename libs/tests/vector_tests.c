#include "../data_structures/vector/vector.c"


void test_create_vector_1() {
    vector v = createVector(4);
    assert(v.size == 0);
    assert(v.capacity == 4);
    deleteVector(&v);
}

void test_create_vector2() {
    vector v = createVector(1);
    assert(v.size == 0);
    assert(v.capacity == 1);
    deleteVector(&v);
}

void test_create_vector3() {
    vector v = createVector(10);
    assert(v.size == 0);
    assert(v.capacity == 10);
    deleteVector(&v);
}

void test_create_vector() {
    test_create_vector_1();
    test_create_vector2();
    test_create_vector3();
}

void test_vector_pushBack1() {
    vector v = createVector(4);
    pushBack(&v, 72);
    assert(v.data[0] == 72);
    deleteVector(&v);
}

void test_vector_pushBack2() {
    vector v = createVector(4);
    pushBack(&v, 72);
    pushBack(&v, 13);
    pushBack(&v, 25);
    assert(v.data[2] == 25);
    deleteVector(&v);
}

void test_vector_pushBack3() {
    vector v = createVector(3);
    pushBack(&v, 72);
    pushBack(&v, 12);
    pushBack(&v, 33);
    assert(v.data[1] == 12);
    deleteVector(&v);
}

void test_vector_pushBack() {
    test_vector_pushBack1();
    test_vector_pushBack2();
    test_vector_pushBack3();
}

void test_atVector_notEmptyVector() {
    vector vector = createVector(3);
    isEmpty(&vector);
    pushBack(&vector, 1);
    pushBack(&vector, 2);
    pushBack(&vector, 3);
    int * ptr_1 = atVector(&vector, 1);
    printf("%d", *ptr_1);
    int * ptr_2 = atVector(&vector, 2);
    printf("%d", *ptr_2);
    int * ptr_3 = atVector(&vector, 3);
    printf("%d", *ptr_3);
}

void test_atVector_requestToLastElement() {
    vector vector = createVector(3);
    isEmpty(&vector);
    pushBack(&vector, 1);
    pushBack(&vector, 2);
    pushBack(&vector, 3);
    int * ptr_1 = back(&vector);
    printf("%d", *ptr_1);
    popBack(&vector);
    int * ptr_2 = back(&vector);
    printf("%d", *ptr_2);
    popBack(&vector);
    int * ptr_3 = back(&vector);
    printf("%d", *ptr_3);
}

void test_back_oneElementInVector() {
    vector vector = createVector(5);
    isEmpty(&vector);
    pushBack(&vector, 1);
    pushBack(&vector, 2);
    pushBack(&vector, 3);
    pushBack(&vector, 4);
    pushBack(&vector, 5);
    popBack(&vector);
    popBack(&vector);
    int* res = back(&vector);
    assert(*res == 3);
}

void test_front_oneElementInVector() {
    vector vector = createVector(3);
    isEmpty(&vector);
    pushBack(&vector, 1);
    pushBack(&vector, 2);
    pushBack(&vector, 3);
    clear(&vector);
    pushBack(&vector, 1);
    pushBack(&vector, 2);
    pushBack(&vector, 3);
    int * ptr =front(&vector);
    printf("%d", *ptr);
}

void test_popBack_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);
    assert(v.size == 1);
    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
}

void test_pushBack_emptyVector() {
    vector vector = createVector(3);
    isEmpty(&vector);
    pushBack(&vector, 1);
    pushBack(&vector, 2);
    pushBack(&vector, 3);
    reserve(&vector, 6);
    pushBack(&vector, 4);
    pushBack(&vector, 5);
    pushBack(&vector, 6);
    bool res = isFull(&vector);
}

