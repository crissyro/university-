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


// 5


// 6


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