#include <stdio.h>
#include <windows.h>


// Ввод массива a размера n
void inputArray(int *a, int n) {
    for (size_t i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
}

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
    return counter < n ? 0 : 1;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    size_t size_a, size_b;

    printf("Введите размер массива a\n");
    scanf("%zu", &size_a);

    printf("Введите размер массива b\n");
    scanf("%zu", &size_b);

    int a[size_a], b[size_b];

    printf("Введите массив a\n");
    inputArray(&a, size_a);

    printf("Введите массив b \n");
    inputArray(&b, size_b);

    int res = Check_Every_A_Elements(a, b, size_a, size_b);

    printf("%d", res);



    return 0;
}
