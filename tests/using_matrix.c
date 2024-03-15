#include "../data_structures/matrix/matrix.c"
#include <math.h>
#include <assert.h>


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
    return sum;
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
    if ((m1.nCols != m2.nCols) || (m1.nRows != m2.nRows))
        return false;

    matrix res = mulMatrices(m1, m2);
    freeMemMatrix(&res);
    return !isEMatrix(&res) ? false : true;
}

// 7
int max(int a, int b) {
    return a > b ? a : b;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m) {
    long long max_main_d = m.values[0][0];
    for (int k = 1; k < m.nRows; ++k) {
        if (max_main_d < m.values[k][k])
            max_main_d = m.values[k][k];
    }
    int n = m.nRows + m.nCols - 1;
    long long *max_values = (long long *)calloc(n, sizeof(long long));
    for (int i = 0; i < m.nRows; i++)
        for (int j = 0; j < m.nCols; j++)
            max_values[i+j] = max(max_values[i+j], m.values[m.nRows - i - 1][j]);

    long long sum = getSum(max_values, n) - max_main_d;
    free(max_values);

    return sum;
}

//8
int getMinInArea(matrix m) {
    position p_max = getMaxValuePos(m);
    int min = INT_MAX;
    for (int i = 0; i < m.nCols; ++i)
        for (int j = 0; j < p_max.rowIndex - abs(p_max.colIndex - i); ++j) {
            if (m.values[j][i] < min)
                min = m.values[j][i];
        }
    return min;
}

// 9

float getSumSq(int *a, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum += pow(a[i], 2);
    return sum;
}

float getDistance(int *a, int n) {
    return sqrtf(getSumSq(a, n));
}

void insertionSortRowsMatrixByRowCriteriaF(matrix m,float (*criteria)(int *, int)) {
    for (int i = 1; i < m.nRows; i++) {
        int j = i;
        while (j > 0 && criteria(m.values[j - 1], m.nCols) > criteria(m.values[j], m.nCols)) {
            float *temp = m.values[j];
            m.values[j] = m.values[j - 1];
            m.values[j - 1] = (int *) temp;
            j--;
        }
    }
}

void sortByDistances(matrix m) {
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}

// 10
int cmp_long_long(const void *pa, const void *pb) {
    long long a = *(long long *)pa;
    long long b = *(long long *)pb;
    return (a > b) - (a < b);
}

int countNUnique(long long *a, int n) {
    int count = 1;
    qsort(a, n, sizeof(long long), cmp_long_long);
    for (int i = 1; i < n; i++) {
        if (a[i] != a[i - 1])
            count++;
    }
    return count;
}

int countEqClassesByRowsSum(matrix m) {
    long long *row_sum = (long long *)calloc(m.nRows, sizeof(long long));
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++)
            row_sum[i] += m.values[i][j];

    }
    int unique_sums = countNUnique(row_sum, m.nRows);
    free(row_sum);
    return unique_sums;
}

// 11
int getNSpecialElement(matrix m) {
    int counter = 0;
    for (int i = 0; i < m.nRows; i++) {
        int max_rows = getMax(m.values[i], m.nCols);
        int sum = getSum(m.values[i], m.nCols) - max_rows;
        if (max_rows > sum)
            counter++;
    }
    return counter;
}

// 12
position getLeftMin(matrix m) {
    position p_min = getMinValuePos(m);
    return p_min;
}

void swapPenultimateRow(matrix m, int n) {
    assert(m.nCols > 1);
    int i = 0, j = 0;
    position p_min = getLeftMin(m);
    while (i < m.nRows && j < m.nCols) {
        int temp = m.values[m.nRows - 2][j];
        m.values[m.nRows - 2][j] = m.values[i][p_min.colIndex];
        m.values[i][p_min.colIndex] =  temp;
        i++;
        j++;
    }
}

// 13
bool isNonDescendingSorted(int *a, int n) {
    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1])
            return false;
    }
    return true;
}

bool hasAllNonDescendingRows(matrix m) {
    for (int i = 0; i < m.nRows; i++) {
        if (!isNonDescendingSorted(m.values[i], m.nCols))
            return false;
    }
    return true;
}

int countNonDescendingRowsMatrices(matrix *ms, int nMatrix) {
    int count = 0;
    for (int i = 0; i < nMatrix; i++) {
        if (hasAllNonDescendingRows(ms[i]))
            count++;
    }
    return count;
}

// 14
int countValues(const int *a, int n, int value) {
    int counter = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == value)
            counter++;
    }
    return counter;
}

int countZeroRows(matrix m) {
    int counter = 0;
    for (int i = 0; i < m.nRows; i++) {
        if (countValues(m.values[i], m.nCols, 0) == m.nCols)
            counter++;
    }
    return counter;
}

void printMatrixWithMaxZeroRows(matrix *ms, int nMatrix) {
    int max_zero_rows = 0;
    for (int i = 0; i < nMatrix; i++) {
        if (countZeroRows(ms[i]) > max_zero_rows)
            max_zero_rows = countZeroRows(ms[i]);
    }
    for (int j = 0; j < nMatrix; j ++) {
        if (countZeroRows(ms[j]) == max_zero_rows)
            outputMatrix(ms[j]);
    }
}

// 15 Дан массив целочисленных квадратных матриц.
// Вывести матрицы с наименьшей нормой.
// В качестве нормы матрицы взять максимум абсолютных величин
//ее элементов.

int matrixNorm(matrix m) {
    int abs_max = 0;
    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            int abs_value = abs(m.values[i][j]);
            if (abs_value > abs_max)
                abs_max = abs_value;
        }
    }
    return abs_max;
}

void output_Matrix_MinNorm(matrix *ms, int nMatrix) {
    int min_norm = matrixNorm(ms[0]);

    for (int i = 1; i < nMatrix; i++) {
        int current_norm = matrixNorm(ms[i]);
        if (current_norm < min_norm)
            min_norm = current_norm;
    }
    for (int i = 0; i < nMatrix; i++) {
        if (matrixNorm(ms[i]) == min_norm)
            outputMatrix(ms[i]);
    }
}

// 16 *Дана матрица.
// Определить 𝑘 – количество "особых" элементов данной матрицы,
// считая элемент "особым" если в строке слева от него находятся только
//меньшие элементы, а справа – только б´oльшие

int min2(int a, int b) {
    return a < b ? a : b;
}

bool isMoreThanLeftEl(int *a, int pos) {
    for (int i = 0; i < pos; i++) {
        if (a[i] > a[pos])
            return false;
    }
    return true;
}

bool isLesThanRightEl(int *a, int n, int pos) {
    for (int i = pos + 1; i < n; i++) {
        if (a[i] < a[pos])
            return false;
    }
    return true;
}

int getNSpecialElement2(matrix m) {
    int counter = 0;
    for (int i = 0; i < m.nRows; i++) {
        int pos = m.nCols / 2;
        bool flag = true;
        while (flag || pos != m.nCols || pos != 0) {
            bool r_res = isLesThanRightEl(m.values[i], m.nCols, pos);
            bool l_res = isMoreThanLeftEl(m.values[i], pos);
            if (r_res && pos == 0 || l_res && pos == m.nCols) {
                counter++;
                break;
            }
            if (r_res && l_res) {
                counter++;
                flag = false;
            } else if (r_res && !l_res)
                pos++;
            else
                pos--;

        }
    }
    return counter;
}

// 17 *Каждая строка данной матрицы представляет собой координаты вектора в
//пространстве.
// Определить, какой из этих векторов образует максимальный угол
//с данным вектором 𝑣.

double getScalarProduct(int *a, int *b, int n) {
    double res = 0;
    for (int i = 0; i < n; i++)
        res += a[i] * b[i];

    return res;
}

double getVectorLength(int *a, int n) {
    double res = getScalarProduct(a, a, n);
    return sqrt(res);
}

double getCosine(int *a, int *b, int n) {
    double scalar_product = getScalarProduct(a, b, n);
    double len_a = getVectorLength(a, n);
    double len_b = getVectorLength(b, n);
    return scalar_product / (len_a * len_b);
}

int getVectorIndexWithMaxAngle(matrix m, int *b) {
    int max_i = 0;
    double max_cos = 1;

    for (int i = 0; i < m.nRows; i++) {
        double cosine = getCosine(m.values[i], b, m.nCols);
        if (cosine < max_cos) {
            max_cos = cosine;
            max_i = i;
        }
    }

    return max_i;
}

// 18  *Дана целочисленная квадратная матрица, все элементы которой различны.
//Найти скалярное произведение строки,
// в которой находится наибольший элемент матрицы, на столбец с наименьшим элементом

long long getScalarProductRowAndCol(matrix m, int i, int j) {
    long long scalar_product = 0;
    for (int k = 0; k < m.nCols; k++)
        scalar_product += m.values[i][k] * m.values[k][j];

    return scalar_product;
}

long long getSpecialScalarProduct(matrix m, int n) {
    long long max_el = m.values[0][0];
    int max_row = 0;
    long long min_element = m.values[0][0];
    int min_col = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (m.values[i][j] > max_el) {
                max_el = m.values[i][j];
                max_row = i;
            }
            if (m.values[i][j] < min_element) {
                min_element = m.values[i][j];
                min_col = j;
            }
        }
    }
    long long special_scalar_product = getScalarProductRowAndCol(m, max_row, min_col);

    return special_scalar_product;
}
