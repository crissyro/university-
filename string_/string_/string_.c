#include "string_.h"


size_t strlen_v1(char *s) {
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

size_t strlen_v2(char *s) {
    int i = 0;
    while (*s != '\0') {
        i++;
        s++;
    }
    return i;
}

size_t strlen_(const char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}


