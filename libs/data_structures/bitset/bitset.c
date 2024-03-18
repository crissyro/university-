#include <stdio.h>
#include <assert.h>

#include "bitset.h"


bitset bitset_create(unsigned setMaxValue) {
    assert (setMaxValue < 32);
    return (bitset) {0, setMaxValue};
}

int bitset_checkValue(bitset *a, unsigned value) {
    return value >= 0 && value <= a->maxValue;
}

bool bitset_in(bitset set, unsigned int value) {
    return set.values &= (1 << value) ? true : false;
}


bool bitset_isEqual(bitset set1, bitset set2) {
    return set1.values == set2.values && set1.maxValue == set2.maxValue ? true : false;
}

bool bitset_isSubset(bitset subset, bitset set) {
    return (set.values & subset.values == set.values && set.maxValue == subset.maxValue) \
 && (set.values != subset.values && set.maxValue != subset.maxValue) ? true : false;
}

void bitset_insert(bitset *set, unsigned int value) {
    set->values |= (1 << value);
}

void bitset_deleteElement(bitset *set, unsigned int value) {
    set->values |= ~(1 << value);
}

bitset bitset_union(bitset set1, bitset set2) {
    bitset set3 = {set1.values | set2.values , set1.maxValue | set2.maxValue};
    return set3;
}

bitset bitset_intersection(bitset set1, bitset set2) {
    assert (set1.maxValue == set2.maxValue);
    return (bitset) {set1.values & set2.values, set1.maxValue};
}

bitset bitset_difference(bitset set1, bitset set2) {
    bitset set3 = {set1.values & ~set2.values , set1.maxValue & ~set2.maxValue};
    return set3;
}

bitset bitset_symmetricDifference(bitset set1, bitset set2) {
    bitset set3 = {set1.values ^ set2.values , set1.maxValue ^ set2.maxValue};
    return set3;
}

bitset bitset_complement(bitset set) {
    bitset result;
    result.values = ~set.values & ((1 << (set.maxValue + 1)) - 1);
    result.maxValue = set.maxValue;
    return result;
}

void bitset_print(bitset set) {
    printf("{");
    int isEmpty = 1;
    for (int i = 0; i <= set.maxValue; ++i) {
        if (bitset_in(set, i)) {
            printf("%d, ", i);
            isEmpty = 0;
        }
    }
    if (isEmpty)
        printf("}\n");
    else
        printf("\b\b}\n");
}