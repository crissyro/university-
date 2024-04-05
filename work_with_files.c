#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "libs/string_/string_/string_.c"
#include "libs/tests/using_string_.c"
#include "libs/data_structures/matrix/matrix.c"
#include "libs/data_structures/vector/vector.c"


void WriteMatricesBinaryFile(char *file_name, FILE *file, matrix *data,int count_matrices) {
    char *c;
    file = fopen(file_name, "wb");

    c = (char *) data;
    for (int i = 0; i < sizeof(matrix) * count_matrices; i++)
        putc(*c++, file);


    fclose(file);
}


void SwapMatricesColsAndRowsFile(char *file_name, FILE *file, int count_matrices) {
    char *c;
    int counter;
    int size = sizeof(matrix) * count_matrices;
    matrix *ptr = malloc(size);
    file = fopen(file_name, "rb");
    c = (char *) ptr;

    while ((counter = getc(file)) != EOF) {
        *c = counter;
        c++;
    }

    for (int j = 0; j < count_matrices; ++j)
        transposeMatrix(&ptr[j]);


    c = (char *) ptr;
    for (int i = 0; i < sizeof(matrix) * count_matrices; i++)
        putc(*c++, file);

    fclose(file);
    free(ptr);
}

void OutputMatricesInFile(char *file_name, FILE *file, int count_matrices) {
    char *c;
    int counter;
    int size = sizeof(matrix) * count_matrices;
    matrix *ptr = malloc(size);
    file = fopen(file_name, "rb");
    c = (char *) ptr;

    while ((counter = getc(file)) != EOF) {
        *c = counter;
        c++;
    }

    outputMatrices(ptr, count_matrices);
    fclose(file);
    free(ptr);
}


void check_Correct_Open_File(FILE *f) {
    if (f == NULL) {
        printf("errno %d\n", errno);
        perror("f");
        exit(1);
    }
}

char *getWayByTasks(char *filename) {
    char *way = __FILE__;
    char *sub_way = str_replace("tasks/F", "F", filename);
    return str_replace(way, __FILE_NAME__, sub_way);
}


void task1() {
    char *name = "task1.txt";
    char *way = getWayByTasks(name);
    FILE file;
    int count_matrices = 3;
    int values[] = {1, 2, 3,
                    1, 2, 3,
                    1, 2, 3,

                    5, 6, 7,
                    5, 6, 7,
                    5, 6, 7,

                    8, 9, 0,
                    8, 9, 0,
                    8, 9, 0 };

    matrix *matrix_array = createArrayOfMatrixFromArray(values, 3, 3, 3);

    WriteMatricesBinaryFile(way, &file, matrix_array,count_matrices);
    SwapMatricesColsAndRowsFile(way, &file, count_matrices);
    OutputMatricesInFile(way, &file, count_matrices);
}

int main() {
    task1();
}

