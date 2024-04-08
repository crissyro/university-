#include "work_with_files.c"


void task1_test() {
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
                    8, 9, 0};

    matrix *matrix_array = createArrayOfMatrixFromArray(values, 3, 3, 3);

    WriteMatricesBinaryFile(way, &file, matrix_array, count_matrices);
    SwapMatricesColsAndRowsFile(way, &file, count_matrices);
    OutputMatricesInFile(way, &file, count_matrices);
    int values_res[] = {1, 1, 1,
                    2, 2, 2,
                    3, 3, 3,

                    5, 5, 5,
                    6, 6, 6,
                    7, 7, 7,

                    8, 8, 8,
                    9, 9, 9,
                    0, 0, 0};
}

void task2_test() {
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
    // генерация чисел осуществляется автоматически
}

void task3_test() {
    srand(time(NULL));

    char *way_input = getWayByTasks("task3.txt");
    FILE *file = fopen(way_input, "w");
    check_Correct_Open_File(file);
    WriteGenerateExpression(file);
    fclose(file);

    fopen(way_input, "r");
    int res = CalculateExpressionFromFile(file);
    fclose(file);

    fopen(way_input, "a");
    fprintf(file, " = %d", res);
    fclose(file);
    // генерация выражений осуществляется автоматически

}

void task4_test() {
    generateRandomWords("task4input.txt");
    printCorrectWords("task4input.txt", "task4output.txt", "a");
    // генерация слов осуществляется автоматически
}

void task5_test() {
    generateRandomStrings("task5input.txt");
    printMaxLenWordsInString("task5input.txt", "task5output.txt");
    // генерация слов осуществляется автоматически
}

void task6_test() {
    generatePolinomialArray("task6.txt", 10, 4);
    printPalinomialWithFile("task6.txt", 10, 4);
    printCorrectPalinomial("task6.txt", 1, 10, 4);
    printPalinomialWithFile("task6.txt", 10, 4);
    // генерация выражений осуществляется автоматически

}

void task7_test() {
    int size = 10;
    int a[size];
    generateArray(a, size);
    outputArray_(a, size);
    generateArrayBinaryFile("task7.txt", a, size);
    sortArrayInFile("task7.txt", size);
    outputArrayFromFile("task7.txt", size);
    // генерация массива осуществляется автоматически
}

void task8_test() {
    char *name = "task8.txt";
    char *way = getWayByTasks(name);
    FILE file;
    int count_matrices = 3;
    int values[] = {1, 2, 3,
                    2, 2, 3,
                    3, 3, 3,

                    5, 6, 7,
                    5, 6, 7,
                    5, 6, 7,

                    8, 9, 0,
                    8, 9, 0,
                    8, 9, 0};

    matrix *matrix_array = createArrayOfMatrixFromArray(values, 3, 3, 3);

    WriteMatricesBinaryFile(way, &file, matrix_array, count_matrices);
    transpocseMatrixIfNotSymetricFile(way, &file, count_matrices);
    OutputMatricesInFile(way, &file, count_matrices);
    int values_res[] = {1, 2, 3,
                        2, 2, 3,
                        3, 3, 3,

                        5, 5, 5,
                        6, 6, 6,
                        7, 7, 7,

                        8, 8, 8,
                        9, 9, 9,
                        0, 0, 0};
}

void task9_test() {
    int size_team = 5;
    int count_sportsmens = 10;
    Sportsman *array = getMemForSportsmensArray(count_sportsmens);
    genereteSportsmens(array, count_sportsmens);
    writeSportsmensInFile("task9.txt", array, count_sportsmens);
    outputSportsmensFromFile("task9.txt", count_sportsmens);
    printf("\n");
    getBestTeam("task9.txt", size_team, count_sportsmens);
    // генерация спортсменов осуществляется автоматически
}

void task10_test() {
    Product *array = getMemForProductArray(7);
    generateProductArray(array);
    outputProducts(array, 7);
    printf("\n");

    Product *arrayC = getMemForProductArray(7);
    generateConsignment(arrayC);
    outputProducts(arrayC,7);

    printf("\n");
    updateBaseProduct(array, arrayC, 7);
    outputProducts(array, 7);
    // генерация продуктов осуществляется автоматически
}

int main() {
    task1_test();
    task2_test();
    task3_test();
    task4_test();
    task5_test();
    task6_test();
    task7_test();
    task8_test();
    task9_test();
    task10_test();
}

