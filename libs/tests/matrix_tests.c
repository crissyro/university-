#include <assert.h>
#include "../data_structures/matrix/matrix.c"


int GetSumRows(int *a, int n) {
    int sum_rows = 0;

    for (int i = 0; i < n; ++i) {
        sum_rows += a[i];
    }

    return sum_rows;
}

void test_getMemMatrix() {
    int nRows = 3;
    int nCols = 4;

    matrix test_matrix = getMemMatrix(nRows, nCols);

    assert(test_matrix.nRows == 3);
    assert(test_matrix.nCols == 4);

    freeMemMatrix(&test_matrix);
}

void test_getMemArrayOfMatrices() {
    int nMatrices = 2;
    int nRows = 3;
    int nCols = 4;

    matrix *ms = getMemArrayOfMatrices(nMatrices, nRows, nCols);

    for (int i = 0; i < nMatrices; i++) {
        assert(ms[i].nRows == nRows && ms[i].nCols == nCols);
    }

    freeMemMatrices(ms, nMatrices);
}


void test_swapRowsColumns() {
    matrix test_matrix = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            },
            3, 3
    );

    swapRows(test_matrix, 0, 2);
    assert(test_matrix.values[0][0] == 7 && test_matrix.values[2][0] == 1);

    swapColumns(test_matrix, 0, 2);
    assert(test_matrix.values[0][0] == 9 && test_matrix.values[0][2] == 7);

    freeMemMatrix(&test_matrix);
}


void test_areTwoMatricesEqual() {
    matrix test_matrix_1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            },
            3, 3
    );

    matrix test_matrix_2 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            },
            3, 3
    );

    matrix test_matrix_3 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    3, 5, 6,
                    7, 8, 9
            },
            3, 3
    );

    assert(areTwoMatricesEqual(&test_matrix_1, &test_matrix_2) == 1);
    assert(areTwoMatricesEqual(&test_matrix_1, &test_matrix_3) == 0);

    freeMemMatrix(&test_matrix_1);
    freeMemMatrix(&test_matrix_2);
    freeMemMatrix(&test_matrix_3);
}

void test_sortRowsColumns() {
    matrix unsorted_matrix = createMatrixFromArray(
            (int[]) {
                    9, 8, 7,
                    6, 5, 4,
                    3, 2, 1
            },
            3, 3
    );

    matrix sorted_matrix = createMatrixFromArray(
            (int[]) {
                    3, 2, 1,
                    6, 5, 4,
                    9, 8, 7
            },
            3, 3
    );

    insertionSortRowsMatrixByRowCriteria(unsorted_matrix, GetSumRows);

    assert(areTwoMatricesEqual(&unsorted_matrix, &sorted_matrix) == 1);

    freeMemMatrix(&unsorted_matrix);
    freeMemMatrix(&sorted_matrix);

}


void test_isEMatrix() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1
            },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    3, 2, 1,
                    6, 5, 4,
                    9, 8, 7
            },
            3, 3
    );
    assert(isEMatrix(&m1) == 1);
    assert(isEMatrix(&m2) == 0);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_isSymmetricMatrix() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1
            },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    3, 2, 1,
                    6, 5, 4,
                    9, 8, 7
            },
            3, 3
    );
    assert(isSymmetricMatrix(&m1) == 1);
    assert(isSymmetricMatrix(&m2) == 0);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_transposeMatrix() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 1, 2, 1,
                    1, 1, 1, 1,
                    1, 1, 1, 1
            },
            3, 4
    );

    transposeMatrix(&m);

    assert(m.nRows == 4);
    assert(m.nCols == 3);
    assert(m.values[2][0] == 2);
}

void test_MinMaxValuesPosition() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    3, 2, 1,
                    6, 5, 4,
                    9, 8, 7
            }, 3 ,3);

    position min_position = getMinValuePos(m);
    assert(min_position.rowIndex == 0 && min_position.colIndex == 2);

    position max_position = getMaxValuePos(m);
    assert(max_position.rowIndex == 2 && max_position.colIndex == 0);

    freeMemMatrix(&m);
}


void test() {
    test_getMemMatrix() ;
    test_getMemArrayOfMatrices();
    test_swapRowsColumns();
    test_sortRowsColumns();
    test_areTwoMatricesEqual();
    test_isEMatrix();
    test_isSymmetricMatrix();
    test_transposeMatrix();
    test_MinMaxValuesPosition();
}

int main() {
    test();
    return 0;
}