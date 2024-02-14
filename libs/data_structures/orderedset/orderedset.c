#include <stdio.h>
#include "orderedset.h"

// возвращает пустое множество, в которое можно вставить capacity элементов
ordered_array_set ordered_array_set_create(size_t capacity) {
    ordered_array_set set;
    set.data = (int *)malloc(capacity * sizeof(int));
    set.size = 0;
    set.capacity = capacity;
    return set;
}

// Сортировка выбором
void swapArrayElements(int *a, int pos1, int pos2) {
    int temp = a[pos1];
    a[pos1] = a[pos2];
    a[pos2] = temp;
}

void arraySort(int *a, size_t *n) {
    for (int i = 0; i < *n; i++) {
        int min_element = a[i];
        int min_element_index = i;

        for (int j = i; j < *n; j++) {
            if (a[j] < min_element) {
                min_element = a[j];
                min_element_index = j;
            }
        }
        swapArrayElements(a, i, min_element_index);
    }
}


// возвращает множество, состоящее из элементов массива a размера size
ordered_array_set ordered_array_set_create_from_array(const int *a, size_t size) {
    arraySort(a, &size);
    ordered_array_set set;
    set.size = size;
    set.capacity = size;
    memcpy(set.data, a, size);
    return set;
}


// возвращает значение позицию элемента в множестве,
// если значение value имеется в множестве set,
// иначе - n
size_t ordered_array_set_in(ordered_array_set *set, int value) {
    return linearSearch_(set->data, set->size, value);
}

// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool ordered_array_set_isEqual(ordered_array_set set1, ordered_array_set set2) {
    return (!memcmp(set1.data, set2.data, set1.size)) ? true : false;
}

//верно ли, что массив В содержит каждый элемент массива А.
int Check_Every_A_Elements(int *a, int *b, size_t n, size_t k) {
    int i = 0;
    int j = 0;
    int counter = 0;
    while (i < k ) {
        if (b[i] == a[j]) {
            counter++;
            i++;
            j++;
        } else {
            i++;
            j++;
        }
    }
    return counter == n ? 1 : 0;
}

// возвращает значение ’истина’, если subset является подмножеством set
// иначе - ’ложь’
bool ordered_array_set_isSubset(ordered_array_set subset, ordered_array_set set) {
    return (Check_Every_A_Elements(subset.data, set.data, subset.size, set.size)) ? true : false;
}

// возбуждает исключение, если в множество по адресу set
// нельзя вставить элемент
void ordered_array_set_isAbleAppend(ordered_array_set *set) {
    assert(set->size < set->capacity);
}

// добавляет элемент value в множество set
void ordered_array_set_insert(ordered_array_set *set, int value) {
    if (ordered_array_set_in(set, value) != -1) {
        ordered_array_set_isAbleAppend(set);
        append_(set->data, (size_t *) set->size, value);
    }
}

// удаляет элемент value из множества set
void ordered_array_set_deleteElement(ordered_array_set *set, int value) {
    size_t pos = linearSearch_(set->data, set->size, value);
    deleteByPosSaveOrder_(set->data, (size_t *) set->size, pos);
}

// возвращает объединение множеств set1 и set2
ordered_array_set ordered_array_set_union(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set set3;
    set3.size = set1.size + set2.size;
    int i = 0;
    int j = 0;
    int l = 0;

    while ( l < set3.size ) {
        if (set1.data[j] <= set2.data[i]) {
            set3.data[l] = set1.data[j];
            j++;
        } else {
            set3.data[l] = set2.data[i];
            i++;
        }
        l++;
    }
    return set3;
}

int CheckSameElements(int const *a, int const *b, size_t elements_a, size_t elements_b) {
    int counter = 0;
    for (size_t i = 0; i < elements_a; i++) {
        for (int j = 0; j < elements_b; j++) {
            if (a[i] == b[j])
                counter++;
        }
    }
    return counter;
}


// возвращает пересечение множеств set1 и set2
ordered_array_set ordered_array_set_intersection(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set set3;
    set3.size = CheckSameElements(set1.data, set2.data, set1.size, set2.size);
    int i = 0;
    int j = 0;
    int l = 0;

    while ( l < set3.size ) {
        if (set2.data[i] < set1.data[j])
            i++;
        else if(set2.data[i] > set1.data[j])
            j++;
        else {
            set3.data[l++] = set2.data[i];
            i++;
            j++;
        }
    }
    for (size_t f = 0; f < set3.size; f++) {
        if (set3.data[f] == set3.data[f + 1])
            deleteByPosSaveOrder_(set3.data, &set3.size, f);
    }
    return set3;
}


int Check_Different_Elements(int const *a, int const *b, size_t elements_a, size_t elements_b) {
    int counter = 0;
    for (int i = 0; i < elements_a; i++) {
        int flag = 0;
        for (int j = 0; j < elements_b; j++) {
            if (a[i] == b[j]) {
                flag = 1;
            }
        }
        if (!flag)
            counter++;
    }
    return counter;
}


// возвращает разность множеств set1 и set2
ordered_array_set ordered_array_set_difference(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set set3;
    set3.size = Check_Different_Elements(set1.data, set2.data, set1.size, set2.size);
    int i = 0;
    int j = 0;
    int l = 0;

    while ( l < set3.size ) {
        if (set1.data[i] == set2.data[j]) {
            i++;
            j++;
        } else {
            set3.data[l++] = set1.data[i++];
            j++;
        }
    }
    return set3;
}

// возвращает симметрическую разность множеств set1 и set2
ordered_array_set ordered_array_set_symmetricDifference(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set set3 = ordered_array_set_difference(set1, set2);
    ordered_array_set set4 = ordered_array_set_difference(set2, set1);
    ordered_array_set set_res = ordered_array_set_union(set3, set4);
    return set_res;
}

int Check_Value(int value, int *b, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (value == b[i])
            return 1;
    }
    return 0;
}

// возвращает дополнение до универсума universumSet множества set
ordered_array_set ordered_array_set_complement(ordered_array_set set, ordered_array_set universumSet) {
    ordered_array_set complement_set;
    complement_set.size = 0;
    complement_set.capacity = universumSet.capacity;
    complement_set.data = (int *)malloc(universumSet.capacity * sizeof(int));

    for (size_t i = 0; i < universumSet.capacity; ++i) {
        if (!Check_Value(universumSet.data[i], set.data, set.size)) {
            complement_set.data[complement_set.size++] = universumSet.data[i];
        }
    }
    free(complement_set.data);
    return complement_set;
}

// вывод множества set
void ordered_array_set_print(ordered_array_set set) {
    outputArray_(set.data, set.size);
}

// освобождает память, занимаемую множеством set
void ordered_array_set_delete(ordered_array_set set) {
    free(set.data);
}