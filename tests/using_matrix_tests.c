#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "using_matrix.c"

void test_swapMinMaxRows() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3
    );



    matrix m2 = createMatrixFromArray(
            (int[]) {
                    7, 8, 9,
                    4, 5, 6,
                    1, 2, 3,
            },
            3, 3
    );

    assert(areTwoMatricesEqual(&m1, &m2) == true);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_sortRowsByMaxElement() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    7, 1, 2,
                    1, 8, 1,
                    3, 2, 3,
            },
            3, 3
    );

    sortRowsByMaxElement(m1);

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    3, 2, 3,
                    7, 1, 2,
                    1, 8, 1,
            },
            3, 3
    );

    matrix m3 = createMatrixFromArray(
            (int[]) {
                    7, 1, 2,
                    1, 8, 1,
                    3, 2, 3,
            },
            3, 3
    );

    assert(areTwoMatricesEqual(&m1, &m2) == true);
    assert(areTwoMatricesEqual(&m1, &m3) == false);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    freeMemMatrix(&m3);
}

void test_sortColsByMinElement() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    3, 5, 2, 4, 3, 3,
                    2, 5, 1, 8, 2, 7,
                    6, 1, 4, 4, 8, 3,
            },
            3, 6
    );

    sortColsByMinElement(m1);


    matrix m2 = createMatrixFromArray(
            (int[]) {
                    5, 2, 3, 3, 3, 4,
                    5, 1, 2, 2, 7, 8,
                    1, 4, 6, 8, 3, 4,
            },
            3, 6
    );

    matrix m3 = createMatrixFromArray(
            (int[]) {
                    3, 5, 2, 4, 3, 3,
                    2, 5, 1, 8, 2, 7,
                    6, 1, 4, 4, 8, 3,
            },
            3, 6
    );

    assert(areTwoMatricesEqual(&m1, &m2) == true);
    assert(areTwoMatricesEqual(&m1, &m3) == false);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    freeMemMatrix(&m3);
}

void test_mulMatrices() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    9, 8, 7,
                    6, 5, 4,
                    3, 2, 1
            },
            3, 3
    );

    matrix expected_result = createMatrixFromArray(
            (int[]) {
                    30, 24, 18,
                    84, 69, 54,
                    138, 114, 90
            },
            3, 3
    );

    matrix result = mulMatrices(m1, m2);

    assert(areTwoMatricesEqual(&result, &expected_result) == true);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    freeMemMatrix(&result);
    freeMemMatrix(&expected_result);
}

void test_getSquareOfMatrixIfSymmetric() {
    matrix symmetric_matrix = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    2, 4, 5,
                    3, 5, 6
            },
            3, 3
    );

    matrix expected_result = createMatrixFromArray(
            (int[]) {
                    14, 25, 31,
                    25, 45, 56,
                    31, 56, 70
            },
            3, 3
    );

    getSquareOfMatrixIfSymmetric(&symmetric_matrix);

    assert(areTwoMatricesEqual(&symmetric_matrix, &expected_result) == true);

    freeMemMatrix(&symmetric_matrix);
    freeMemMatrix(&expected_result);
}

void test_transposeIfMatrixHasNotEqualSumOfRows() {
    matrix input_matrix = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            },
            3, 3
    );

    matrix expected_result = createMatrixFromArray(
            (int[]) {
                    1, 4, 7,
                    2, 5, 8,
                    3, 6, 9
            },
            3, 3
    );

    transposeIfMatrixHasNotEqualSumOfRows(input_matrix);

    assert(areTwoMatricesEqual(&input_matrix, &expected_result) == true);

    freeMemMatrix(&input_matrix);
    freeMemMatrix(&expected_result);
}

void test_isMutuallyInverseMatrices() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2,
                    3, 4
            },
            2, 2
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 2,
                    3, 5
            },
            2, 2
    );

    assert(isMutuallyInverseMatrices(m1, m2) == false);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}

void test_findSumOfMaxesOfPseudoDiagonal() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    3, 2, 5, 4,
                    1, 3, 6, 3,
                    3, 2, 1, 2
            },
            3, 4
    );

    long long result = findSumOfMaxesOfPseudoDiagonal(m);

    assert(result == 23);

    freeMemMatrix(&m);
}

void test_getMinInArea() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    3, 2, 5, 4, 9, 9,
                    1, 3, 6, 0, 9, 9,
                    3, 2, 1, 2, 9, 9,
                    3, 2, 5, 8, 9, 9,
                    1, 3, 6, 12, 9, 9,
            },
            5, 6
    );

    int expected_result = 0;

    int result = getMinInArea(m);

    assert(result == expected_result);

    freeMemMatrix(&m);
}

void test_insertionSortRowsMatrixByRowCriteriaF() {
    matrix input_matrix = createMatrixFromArray(
            (int[]) {
                    9, 8, 7,
                    6, 5, 4,
                    3, 2, 1
            },
            3, 3
    );

    insertionSortRowsMatrixByRowCriteriaF(input_matrix, getDistance);

    for (int i = 1; i < input_matrix.nRows; i++) {
        assert(getDistance(input_matrix.values[i - 1], input_matrix.nCols) <= getDistance(input_matrix.values[i], input_matrix.nCols));
    }

    freeMemMatrix(&input_matrix );
}

void test_countEqClassesByRowsSum() {
    matrix input_matrix = createMatrixFromArray(
            (int[]) {
                    7, 1,
                    2, 7,
                    5, 4,
                    4, 3,
                    1, 6,
                    8, 0
            },
            6, 2
    );

    int classes = countEqClassesByRowsSum(input_matrix);

    assert(classes == 3);

    freeMemMatrix(&input_matrix);
}

void test_getNSpecialElement() {
    matrix input_matrix = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9
            },
            3, 3
    );

    int k = getNSpecialElement(input_matrix);

    assert(k == 2);

    freeMemMatrix(&input_matrix);
}

void test_swapPenultimateRow() {
    matrix input_matrix = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 1
            },
            3, 3
    );

    matrix expected_result = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    1, 4, 7,
                    7, 8, 1
            },
            3, 3
    );

    matrix input_matrix1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3, 4,
                    4, 5, 6, 4,
                    7, 8, 1, 4,
                    7, 0, 9, 3
            },
            4, 4
    );

    matrix expected_result1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3, 4,
                    4, 5, 6, 4,
                    2, 5, 8, 0,
                    7, 0, 9, 3
            },
            4, 4
    );

    swapPenultimateRow(input_matrix1, input_matrix1.nRows);

    assert(areTwoMatricesEqual(&input_matrix, &expected_result) == true);
    assert(areTwoMatricesEqual(&input_matrix1, &expected_result1) == true);

    freeMemMatrix(&input_matrix);
    freeMemMatrix(&expected_result);
    freeMemMatrix(&input_matrix1);
    freeMemMatrix(&expected_result1);
}

void test_countNonDescendingRowsMatrices() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 6,
                    2, 2
            },
            2, 2
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    5, 4,
                    2, 3
            },
            2, 2
    );

    matrix m3 = createMatrixFromArray(
            (int[]) {
                    1, 3,
                    7, 9,
            },
            2, 2
    );

    matrix a[] = {m1, m2, m3};

    int count_matrix = countNonDescendingRowsMatrices(a, 3);

    assert(count_matrix == 2);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    freeMemMatrix(&m3);
}

void test_countZeroRows() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 6,
                    2, 2
            },
            2, 2
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    0, 0,
                    2, 3
            },
            2, 2
    );

    matrix m3 = createMatrixFromArray(
            (int[]) {
                    0, 0,
                    0, 0,
            },
            2, 2
    );

    matrix a[] = {m1, m2, m3};

    assert(countZeroRows(a[0]) == 0);
    assert(countZeroRows(a[1]) == 1);
    assert(countZeroRows(a[2]) == 2);

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    freeMemMatrix(&m3);
}

void test_getNSpecialElement2() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    2, 3, 5, 5, 4,
                    6, 2, 3, 8, 12,
                    12, 12, 2, 1, 2,
            },
            3, 5
    );

    int expected_result = 4;

    int result = getNSpecialElement2(m);

    assert(result == expected_result);

    freeMemMatrix(&m);
}

void test_getVectorIndexWithMaxAngle() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3
    );

    int b[] = {1, 0, 0};

    int max_angle_index = getVectorIndexWithMaxAngle(m, b);

    assert(max_angle_index == 0);

    freeMemMatrix(&m);
}

void test_getSpecialScalarProduct() {
    matrix m = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3
    );

    int special_scalar_product = getSpecialScalarProduct(m, 3);

    assert(special_scalar_product == 102);

    freeMemMatrix(&m);
}

void test() {
    test_swapMinMaxRows() ;
    test_sortRowsByMaxElement() ;
    test_sortColsByMinElement() ;
    test_mulMatrices() ;
    test_getSquareOfMatrixIfSymmetric() ;
    test_transposeIfMatrixHasNotEqualSumOfRows() ;
    test_isMutuallyInverseMatrices() ;
    test_findSumOfMaxesOfPseudoDiagonal() ;
    test_getMinInArea() ;
    test_insertionSortRowsMatrixByRowCriteriaF() ;
    test_countEqClassesByRowsSum() ;
    test_getNSpecialElement() ;
    test_swapPenultimateRow() ;
    test_countNonDescendingRowsMatrices() ;
    test_countZeroRows() ;
    test_getNSpecialElement2() ;
    test_getVectorIndexWithMaxAngle() ;
    test_getSpecialScalarProduct() ;
}

int main() {
    test();

    return 0;
}