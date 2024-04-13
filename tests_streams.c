#include "work_with_streams.c"

void task1() {
    int size_main_matrix = 3;
    int count_submatrix = 2;
    matrix pos_array = getMemMatrix(count_submatrix, 4);
    generateSubMatrixArray(size_main_matrix, pos_array);
    outputMatrix(pos_array);
    matrix main_matrix = getMemMatrix(size_main_matrix, size_main_matrix);
    updateMatrixSubMatrices(main_matrix, pos_array);
    outputMatrix(main_matrix);
}

void task2() {
    matrix m = getMemMatrix(4, 3);
    inputMatrix(&m);
    outputMatrix(m);
    lifeGameStep(m);
    outputMatrix(m);
}

void task3() {
    matrix m = getMemMatrix(3, 3);
    inputMatrix(&m);
    outputMatrix(m);
    medianFilter3(m);
    outputMatrix(m);
}

void task4() {
    Domain domain;
    char *s[] = { "900 google.mail.com", "50yahoo.com", "1 intel.mail.com", "5 wiki.org"};
    Domain *res = getMemDomainArray(10);
    int size = 0;
    domain = getDomain(s[0]);
    addAllDomain(res, &size, domain);
    domain = getDomain(s[1]);
    addAllDomain(res, &size, domain);
    domain = getDomain(s[2]);
    addAllDomain(res, &size, domain);
    domain = getDomain(s[3]);
    addAllDomain(res, &size, domain);

    for (int i = 1; i <= size; ++i) {
        printf("%d %s\n", res[i].count_used, res[i].way);
    }
}

void task6() {
    printf("%d",GetMinNumByPattern("DDD"));
}


void task5() {
    matrix m = getMemMatrix(3, 3);
    inputMatrix(&m);
    printf("%d", GetCountUnitSubMatrices(m));
}


void task7() {
    binaryTree *tree = NULL;
    push(tree, 6);
    push(tree, 2);
    push(tree, 1);
    push(tree, 0);
    push(tree, 3);
    printInDepthRecursively(tree);
}

void task8() {
    char s[] = "abap";
    int indices[] = {0, 3, 2, 1};
    int indicesSize = 4;

    char* resString = makeStringFromIndeces(s, indices, indicesSize);

    printf("%s\n", resString);

    free(resString);
}

void task9() {
    srand(time(NULL));

    int N;

    scanf("Input N: %d ", &N);

    int count_num = 10;
    char *way_input = getWayByTasks("task9input.txt");
    FILE *file_input = fopen(way_input, "w");
    check_Correct_Open_File(file_input);
    GenerateRandomIntNumbers(file_input, count_num);
    fclose(file_input);

    int numbers[count_num];
    fopen(way_input, "r");
    check_Correct_Open_File(way_input);
    ReadIntNumbers(file_input, numbers, &count_num);
    fclose(file_input);

    for (int i = 0; i < count_num; i++) {
        if (numbers[i] >= N)
            deleteByPosSaveOrder_(numbers, &count_num, i);
    }

    char *way_output = getWayByTasks("task9output.txt");
    FILE *file_output = fopen(way_output, "w");
    check_Correct_Open_File(file_output);
    WriteIntNumbers(file_output, numbers, count_num);
    fclose(file_output);
}

int main() {
    //task1();
    //task2();
    //task3();
    //task4();
    //task5();
    //task6();
    //task7();
    //task8();
    //task9();
    //task10();

    return 0;
}