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



void task7() {
    binaryTree *tree = NULL;
    push(tree, 6);
    push(tree, 2);
    push(tree, 1);
    push(tree, 0);
    push(tree, 3);
    printInDepthRecursively(tree);
}

int main() {
    //task1();
    //task2();
    //task3();


    task7();
}