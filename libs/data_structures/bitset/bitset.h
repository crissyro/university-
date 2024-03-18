#ifndef INC_BITSET_H
#define INC_BITSET_H

#include <stdint.h>
#include <stdbool.h>

typedef struct bitset {
    uint32_t values; // множество
    uint32_t maxValue; // максимальный элемент универсума
} bitset;

// возвращает пустое множество c универсумом 0, 1,..., maxValue
bitset bitset_create(unsigned maxValue);


int bitset_checkValue(bitset *a, unsigned value);

// возвращает значение ’истина’, если значение value имеется в множестве set
// иначе - ’ложь’
bool bitset_in(bitset set, unsigned int value);

// возвращает значение ’истина’, если множества set1 и set2 равны
// иначе - ’ложь’
bool bitset_isEqual(bitset set1, bitset set2);

// возвращает значение ’истина’ если множество subset
// является подмножеством множества set, иначе - ’ложь’.
bool bitset_isSubset(bitset subset, bitset set);

// добавляет элемент value в множество set
void bitset_insert(bitset *set, unsigned int value);

// удаляет элемент value из множества set
void bitset_deleteElement(bitset *set, unsigned int value);

// возвращает объединение множеств set1 и set2
bitset bitset_union(bitset set1, bitset set2);

// возвращает пересечение множеств set1 и set2
bitset bitset_intersection(bitset set1, bitset set2);

// возвращает разность множеств set1 и set2
bitset bitset_difference(bitset set1, bitset set2);

// возвращает симметрическую разность множеств set1 и set2
bitset bitset_symmetricDifference(bitset set1, bitset set2);

// возвращает дополнение до универсума множества set
bitset bitset_complement(bitset set);

// вывод множества set
void bitset_print(bitset set);

#endif