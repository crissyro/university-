#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void inputArray(int *a, int *n) {
    for (size_t i = 0; i < *n; i++)
        scanf("%d", &a[i]);
}

void outputArray(const int *a, int *n) {
    for (size_t i = 0; i < *n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void qsort(void *ptr, size_t count, size_t size, int (*comp)(const void *, const void *));

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *) a;
    int arg2 = *(const int *) b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int BionarySearch(int *a, int n, int value) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (a[middle] < value)
            left = middle + 1;
        else if (a[middle] > value)
            right = middle - 1;
        else
            return middle;
    }
    return -1;
}

/*int BionarySearchRight(int *a, int n, int value) {
    int left = -1;
    int right = n;
    while (right > left + 1) {
        int middle = (left + right) / 2;
        if (a[middle] < value)
            left = middle;
        else
            right = middle;
    }
    if (a[right] > a[n - 1] || a[right] < a[n - 1])
        return a[n - 1];
    else
        return a[right];
}*/

int BinarySearchLeft(int *a, int n, int value) {
    int left = -1;
    int right = n;
    while (right > left + 1) {
        int middle = (left + right) / 2;
        if (a[middle] <= value)
            left = middle;
        else
            right = middle;
    }
    return left;
}

int BinarySearchupper(int *a, size_t n, int x) {
    int l = 0;
    int r = n - 1;
    int result = -1;
    while (l <= r) {
        int m = l + (r - l) / 2;

        if (a[m] > x) {
            result = m;
            l = m + 1;
        } else
            r = m - 1;
    }

    return result;
}

int BinarySearchUpper_(int *a, int l, int r, int x) {
    if (l > r)
        return -1;

    int m = l + (r - l) / 2;
    if (a[m] > x) {
        int res = BinarySearchUpper_(a, m + 1, r, x);
        if (res == -1)
            return m;
        else
            return res;
    } else
        return BinarySearchUpper_(a, l, m - 1, x);
}
int BinarySearchUpper(const int *a, int n, int x) {
    return BinarySearchUpper_(a, 0, n - 1, x);
}


int main() {
    int n;

    scanf("%d", &n);

    int a[n];
    inputArray(a, &n);
    int res = BinarySearchUpper(a,n, 5);
    printf("%d", res);


    return 0;
}
