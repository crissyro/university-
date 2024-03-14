#include "../data_structures/matrix/matrix.c"

// 1
void swap_Min_Max_Rows(matrix *m) {
    position i_min = getMinValuePos(*m);
    position i_max = getMaxValuePos(*m);
    swapRows(*m, i_min.rowIndex, i_max.rowIndex);
}

// 2
int getMax(int *a, int n) {
    int max = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > a[0])
            max = a[i];
    }
    return max;
}

void sortRowsByMaxElement(matrix m) {
    for (int i = 0; i < m.nRows - 1; i++) {
        for (int j = 0; j < m.nRows - i - 1; j++) {
            if (getMax(m.values[j], m.nCols) > getMax(m.values[j + 1], m.nCols)) {
                swapRows(m, j, j + 1);
            }
        }
    }
}

// 3
int getMin(int *a, int n) {
    int min = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < min)
            min = a[i];
    }

    return min;
}

void sortColsByMinElement(matrix m) {
    matrix a = getMemMatrix(m.nCols, m.nRows);

    for (int j = 0; j < m.nCols; j++) {
        for (int k = 0; k < m.nRows; k++) {
            a.values[j][k] = m.values[k][j];
        }
    }

    for(int i = 0; i < m.nCols-1; i++) {
        int col1_min = getMin(a.values[i], m.nRows);
        int col2_min = getMin(a.values[i + 1], m.nRows);

        if ((col1_min >= col2_min) || (i == m.nCols-2 && col1_min < col2_min)) {
            swapColumns(m, i, i + 1);
        }
    }
    freeMemMatrix(&a);
}


// 4
matrix mulMatrices(matrix m1, matrix m2) {
    matrix res = getMemMatrix(m1.nRows, m2.nCols);

    for (int i = 0; i < m1.nRows; i++) {
        for (int j = 0; j < m2.nCols; j++) {
            res.values[i][j] = 0;
            for (int l = 0; l < m1.nCols; l++)
                res.values[i][j] += m1.values[i][l] * m2.values[l][j];
        }
    }
    return res;
}

void getSquareOfMatrixIfSymmetric(matrix *m) {
    if (isSymmetricMatrix(m) && isSquareMatrix(m))
        *m =  mulMatrices(*m , *m);
    freeMemMatrix(m);
}

// 5
bool isUnique(long long *a, int n) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            if (a[i] == a[j])
                return false;
        }
    return true;
}

long long getSum(int *a, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
}

void transposeIfMatrixHasNotEqualSumOfRows(matrix m) {
    long long sum_array[m.nRows];
    for (int i = 0; i < m.nRows; i++) {
        sum_array[i] = getSum(m.values, m.nCols);
    }
    if (isUnique(sum_array, m.nRows))
        transposeMatrix(&m);

}

// 6
bool isMutuallyInverseMatrices(matrix m1, matrix m2) {

}

// 7


//8

// 9


// 10


// 11

// 12


// 13


// 14


// 15


// 16


// 17


// 18