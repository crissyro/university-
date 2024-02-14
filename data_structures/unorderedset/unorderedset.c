#include "unorderedset.h"


// возвращает пустое множество для capacity элементов
unordered_array_set unordered_array_set_create(size_t capacity) {
    unordered_array_set set = {
            malloc(sizeof(int) * capacity),
            0,
            capacity
    };
    unordered_array_set_delete(set);
    return set;
}

static void unordered_array_set_shrink_to_fit(unordered_array_set *a){
    if (a->size != a->capacity) {
        a->data = (int*)realloc(a->data, sizeof(int)*a->size);
        a->capacity = a->size;
    }
    unordered_array_set_delete(*a);
}

// возвращает множество, состоящее из элементов массива a размера size
unordered_array_set unordered_array_set_create_from_array(const int *a, size_t size) {
    unordered_array_set set = unordered_array_set_create(size);
    for (size_t i = 0; i < size; i++)
        unordered_array_set_insert(&set, a[i]);
    unordered_array_set_shrink_to_fit(&set);
    return set;
}

// возвращает позицию элемента в множестве,
// если значение value имеется в множестве set, иначе - n
int unordered_array_set_in(unordered_array_set *set, int value) {
    return linearSearch_(set->data, set->size, value);
}


int check_All_Elements(int *a, int *b, size_t n, size_t k) {
    int counter = 0;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < k; j++) {
            if (b[j] == a[i])
                counter++;
        }
    return counter < n ? 0 : 1;
}



// возвращает истину если subset является подмножеством set, иначе ложь
bool unordered_array_set_isSubset(unordered_array_set subset, unordered_array_set set) {
    return (check_All_Elements(subset.data, set.data, subset. size, set.size)) ? true : false;
}

int check_Same_Arrays(int *a, int *b, size_t n, size_t k) {
    int counter = 0;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < k; j++) {
            if (b[j] == a[i])
                counter++;
        }
    return (counter == n && n == k) ? 1 : 0;
}


// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool unordered_array_set_isEqual(unordered_array_set set1, unordered_array_set set2) {
    return (check_Same_Arrays(set1.data, set2.data, set1.size, set2.size)) ? true : false;
}

// возбуждает исключение, если в множество по адресу set
// нельзя вставить элемент
void unordered_array_set_isAbleAppend(unordered_array_set *set) {
    assert(set->size < set->capacity);
}

// добавляет элемент value в множество set
void unordered_array_set_insert(unordered_array_set *set, int value) {
    if (unordered_array_set_in(set, value) != -1) {
        unordered_array_set_isAbleAppend(set);
        append_(set->data, (size_t *) set->size, value);
    }
}

// удаляет элемент value из множества set
void unordered_array_set_deleteElement(unordered_array_set *set, int value) {
    size_t pos = linearSearch_(set->data, set->size, value);
    deleteByPosSaveOrder_(set->data, (size_t *) set->size, pos);
}

// возвращает объединение множеств set1 и set2
unordered_array_set unordered_array_set_union(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set set3;
    set3.size = 0;
    set3.capacity = set1.size + set2.size;
    set3.data = (int *)malloc(set3.capacity * sizeof(int));
    for (size_t i = 0; i < set1.size; i++) {
        set3.data[set3.size++] = set1.data[i];
    }
    for (size_t i = 0; i < set2.size; i++) {
        int flag = 0;
        for (size_t j = 0; j < set3.size; j++) {
            if (set3.data[j] == set2.data[i]) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            set3.data[set3.size++] = set2.data[i];
        }
    }
    unordered_array_set_delete(set3);
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
unordered_array_set unordered_array_set_intersection(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set set3;
    set3.size = 0;
    set3.capacity = CheckSameElements(set1.data, set2.data, set1.size, set2.size);
    set3.data = (int *)malloc(set3.capacity * sizeof(int));
    for (size_t i = 0; i < set1.size; i++)
        for (size_t j = 0; j < set2.size; j++) {
            if (set1.data[i] == set2.data[j]) {
                append_(set3.data, (size_t *) set3.size, set1.data[i]);
            }
        }
    unordered_array_set_delete(set3);
    return set3;
}

int Check_Value(int value, int *b, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (value == b[i])
            return 1;
    }
    return 0;
}

// возвращает разность множеств set1 и set2
unordered_array_set unordered_array_set_difference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set set3;
    set3.size = 0;
    set3.capacity = set1.capacity;
    set3.data = (int *)malloc(set3.capacity * sizeof(int));
    for (size_t i = 0; i < set1.size; i++) {
        if (!Check_Value(set1.data[i], set2.data, set2.size)) {
            append_(set3.data, (size_t *) set3.size, set1.data[i]);
        }
    }
    unordered_array_set_delete(set3);
    return set3;
}

// возвращает дополнение до универсума множества set
unordered_array_set unordered_array_set_complement(unordered_array_set set, unordered_array_set universumSet) {
    unordered_array_set complement_set;
    complement_set.size = 0;
    complement_set.capacity = universumSet.capacity;
    complement_set.data = (int *)malloc(universumSet.capacity * sizeof(int));

    for (size_t i = 0; i < universumSet.capacity; ++i) {
            if (!Check_Value(universumSet.data[i], set.data, set.size)) {
                complement_set.data[complement_set.size++] = universumSet.data[i];
        }
    }
    unordered_array_set_delete(complement_set);
    return complement_set;
}

// возвращает симметрическую разность множеств set1 и set2
unordered_array_set unordered_array_set_symmetricDifference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set set3 =unordered_array_set_difference(set1, set2);
    unordered_array_set set4 =unordered_array_set_difference(set2, set1);
    unordered_array_set set_res = unordered_array_set_union(set3, set4);
    return set_res;
}

// вывод множества set
void unordered_array_set_print(unordered_array_set set) {
    outputArray_(set.data, set.size);
}

// освобождает память, занимаемую множеством set
void unordered_array_set_delete(unordered_array_set set) {
    free(set.data);
}
