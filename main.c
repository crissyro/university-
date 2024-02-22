#include <stdio.h>
#include <stdbool.h>
#include "libs/algorithms/array/array.c"

# include <memory.h>

#define MAX_SIZE 100

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


typedef struct ordered_array_set {
    int data[MAX_SIZE];
    size_t size;
} ordered_array_set;

ordered_array_set ordered_array_set_create(size_t size) {
    ordered_array_set set = {
            {0},
            size,
    };
    return set;

}

// возвращает множество, состоящее из элементов массива a размера size
ordered_array_set ordered_array_set_create_from_array(const int *a, size_t size) {
    ordered_array_set set = ordered_array_set_create(size);
    for (size_t i = 0; i < size; i++)
        set.data[i] = a[i];

    return set;
}

// возвращает позицию элемента в множестве,
// если значение value имеется в множестве set, иначе - n
int ordered_array_set_in(ordered_array_set *set, int value) {
    return linearSearch_(set->data, set->size, value);
}

//верно ли, что массив В содержит каждый элемент массива А.
int Check_Every_A_Elements(int *a, int *b, size_t n, size_t k) {
    int i = 0;
    int j = 0;
    int counter = 0;
    while (i < k) {
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

// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool ordered_array_set_isEqual(ordered_array_set set1, ordered_array_set set2) {
    return (!memcmp(set1.data, set2.data, set1.size)) ? true : false;
}


// добавляет элемент value в множество set
void ordered_array_set_insert(ordered_array_set *set, int value) {
    if (ordered_array_set_in(set, value) != -1) {
        append_(set->data, (size_t *) set->size, value);
    }
}

// удаляет элемент value из множества set
void ordered_array_set_deleteElement(ordered_array_set *set, int value) {
    size_t pos = linearSearch_(set->data, set->size, value);
    deleteByPosSaveOrder_(set->data, (size_t *) set->size, pos);
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

// возвращает объединение множеств set1 и set2
ordered_array_set ordered_array_set_union(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set set3;
    set3.size = set1.size + set2.size - CheckSameElements(set1.data, set2.data, set1.size, set2.size);
    int i = 0;
    int j = 0;
    int l = 0;

    while (l < set3.size) {
        if (set2.size > j && set1.data[j] < set2.data[i]) {
            set3.data[l] = set1.data[j];
            j++;
        } else if (set1.data[j] == set2.data[i]) {
            set3.data[l] = set1.data[j];
            i++;
            j++;
        } else {
            set3.data[l] = set2.data[i];
            i++;
        }
        l++;
    }
    arraySort(set3.data, &set3.size);
    return set3;
}

// возвращает пересечение множеств set1 и set2
ordered_array_set ordered_array_set_intersection(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set set3;
    set3.size = CheckSameElements(set1.data, set2.data, set1.size, set2.size);
    int i = 0;
    int j = 0;
    int l = 0;

    while (l < set3.size) {
        if (set2.data[i] < set1.data[j])
            i++;
        else if (set2.data[i] > set1.data[j])
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

    while (l < set3.size) {
        if (j >= set2.size || set1.data[i] < set2.data[j]) {
            set3.data[l] = set1.data[i];
            l++;
            i++;
        } else if (set1.data[i] > set2.data[j]) {
            j++;
        } else {
            i++;
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


// вывод множества set
void ordered_array_set_print(ordered_array_set set) {
    outputArray_(set.data, set.size);
}

ordered_array_set ordered_array_set_universum_create(size_t size) {
    ordered_array_set universum_set;
    universum_set.size = size;
    int value = 1;
    for (size_t i = 0; i < size; i++) {
        universum_set.data[i] = value++;
    }
    return universum_set;
}

// Проверка элемента на строгое включение в множество
int isProperSubsetOrdered(ordered_array_set set1, ordered_array_set set2) {
    if (set1.size >= set2.size) {
        return 0; // Если размер первого множества больше или равен размеру второго, нет
        //строгого включения
    }
    int i = 0, j = 0;
    while (i < set1.size && j < set2.size) {
        if (set1.data[i] == set2.data[j]) {
            i++;
            j++;
        } else if (set1.data[i] < set2.data[j]) {
            return 0; // Если первое множество содержит элемент, которого нет во втором,
            //то нет строгого включения
        } else {
            j++;
        }
    }
    if (i == set1.size) {
        return 1; // Если все элементы первого множества входят во второе и размеры
        //различны, есть строгое включение
    }
    return 0;
}

bool containsArray(int *a, int *b, size_t n, size_t m) {
    bool contains = false;
    for (int i = 0; i <= n - m; i++) {
        bool match = true;
        for (int j = 0; j < m; j++) {
            if (a[i + j] != b[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            contains = true;
            break;
        }
    }
    return contains;
}

bool areArraysEqual(int *a, int *b, size_t n, size_t m) {
    if (n != m) {
        return false;
    }

    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    ordered_array_set A;
    A.size = 7;

    ordered_array_set B;
    B.size = 5;

    ordered_array_set C;
    C.size = 5;

    printf("input A elements\n");
    inputArray_(A.data, A.size);

    printf("input B elements\n");
    inputArray_(B.data, B.size);

    printf("input C elements\n");
    inputArray_(C.data, C.size);

    ordered_array_set set1 = ordered_array_set_symmetricDifference(A, B);
    ordered_array_set_print(set1);
    ordered_array_set D = ordered_array_set_symmetricDifference(set1, C);
    ordered_array_set_print(D);

    return 0;
}
