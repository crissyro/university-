#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "libs/string_/string_/string_.c"
#include "libs/tests/using_string_.c"
#include "libs/data_structures/matrix/matrix.c"
#include "libs/data_structures/vector/vector.c"
#include <time.h>


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


void GenerateRandomFloatNumbers(FILE *file, int count) {
    for (int i = 0; i < count; i++) {
        double number = ((double)rand() / RAND_MAX) * 1000.0;
        fprintf(file, "%lf\n", number);
    }
}

void ReadFloatNumbers(FILE *file, double numbers[], int *count) {
    *count = 0;
    while (fscanf(file, "%lf", &numbers[*count]) == 1)
        (*count)++;

}

void WriteFloatNumbers(FILE *file, double numbers[], int count) {
    for (int i = 0; i < count; i++)
        fprintf(file, "%.2f\n", numbers[i]);

}

void task2() {
    srand(time(NULL));

    int count_num = 10;
    char *way_input = getWayByTasks("task2input.txt");
    FILE *file_input = fopen(way_input, "w");
    check_Correct_Open_File(file_input);
    GenerateRandomFloatNumbers(file_input, count_num);
    fclose(file_input);

    double numbers[count_num];
    fopen(way_input, "r");
    check_Correct_Open_File(way_input);
    ReadFloatNumbers(file_input, numbers, &count_num);
    fclose(file_input);

    char *way_output = getWayByTasks("task2output.txt");
    FILE *file_output = fopen(way_output, "w");
    check_Correct_Open_File(file_output);
    WriteFloatNumbers(file_output, numbers, count_num);
    fclose(file_output);
}

char generateRandomOperator() {
    char operators[] = {'+', '-', '*', '/'};
    return operators[rand() % 4];
}

void WriteGenerateExpression(FILE *file) {
    srand(time(NULL));

    int num1 = (int) rand() % 9 + 1;
    int num2 = (int) rand() % 9 + 1;
    int num3 = (int) rand() % 9 + 1;

    int operator1  = generateRandomOperator();
    int operator2  = generateRandomOperator();

    if ((int) rand() % 2)
        fprintf(file, "%d %c %d %c %d", num1, operator1, num2, operator2, num3);
    else
        fprintf(file, "%d %c %d", num1, operator1, num2);
}

int applyOperator(char operator, int operand1, int operand2) {
    switch (operator) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return operand1 / operand2;
    }
}

int CalculateExpressionFromFile(FILE *file) {
    int num1, num2, num3, res;
    num3 = 0;
    char operator1, operator2;

    fscanf(file, "%d %c %d %c %d", &num1, &operator1, &num2, &operator2, &num3);

    if (num3 == 0) 
        res = applyOperator(operator1, num1, num2);
    else {
        if (operator1 == '/' || operator1 == '*')
            res = applyOperator(operator2, applyOperator(operator1, \
            num1, num2), num3);
        else 
            res = applyOperator(operator1, num1, \
            applyOperator(operator2, num2, num3));
    }

    return res;
}

void task3() {
    srand(time(NULL));

    char *way_input = getWayByTasks("task3.txt");
    FILE *file = fopen(way_input, "w");
    WriteGenerateExpression(file);
    fclose(file);

    fopen(way_input, "r");
    int res =  CalculateExpressionFromFile(file);
    fclose(file);

    fopen(way_input, "a");
    fprintf(file," = %d", res);
    fclose(file);

}

void generateRandomWords(const char* filename) {
    char* way = getWayByTasks(filename);
    FILE* file = fopen(way, "w");

    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    int alphabet_length = strlen(alphabet);

    srand(time(NULL));

    for (int i = 0; i < MAX_N_WORDS_IN_STRING; i++) {
        char word[10];
        int word_length = rand() % (9) + 1;

        for (int j = 0; j < word_length; j++)
            word[j] = alphabet[rand() % alphabet_length];

        word[word_length] = '\0';
        fprintf(file, "%s\n", word);
    }

    fclose(file);
}

void printCorrectWords(char* inputFilename, char* outputFilename, char* sequence) {
    char* way_input = getWayByTasks(inputFilename);
    FILE* file_input = fopen(way_input, "r");

    char* way_output = getWayByTasks(outputFilename);
    FILE* file_output = fopen(way_output, "w");

    char word[MAX_N_WORDS_IN_STRING];

    while (fscanf(file_input, "%s", word) == 1) {
        if (strstr(word, sequence))
            fprintf(file_output, "%s\n", word);
    }

    fclose(file_input);
    fclose(file_output);
}

void task4() {
    srand(time(NULL));
    generateRandomWords("task4input.txt");
    printCorrectWords("task4input.txt", "task4output.txt", "a");
}

int main() {
   task1();
   task2();
   task3();
   task4();
}

