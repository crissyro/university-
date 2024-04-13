#include "libs/data_structures/matrix/matrix.c"
#include <time.h>
#include "libs/algorithms/array/array.c"
#include <string.h>
#include "libs/tests/using_string_.c"
#include <limits.h>



void generateSubMatrixArray(int size_main_matrix, matrix sub_matrix_array) {
    srand(time(NULL));

    for (int i = 0; i < sub_matrix_array.nRows; ++i) {
        sub_matrix_array.values[i][0] = rand() % size_main_matrix;
        sub_matrix_array.values[i][1] = rand() % size_main_matrix;

        sub_matrix_array.values[i][2] =
                sub_matrix_array.values[i][0] + rand() % (size_main_matrix - sub_matrix_array.values[i][0]);
        sub_matrix_array.values[i][3] =
                sub_matrix_array.values[i][1] + rand() % (size_main_matrix - sub_matrix_array.values[i][1]);
    }
}

void updateMatrixSubMatrices(matrix main_matrix, matrix sub_matrix_array) {
    for (int i = 0; i < sub_matrix_array.nRows; ++i) {
        for (int j = sub_matrix_array.values[i][0]; j <= sub_matrix_array.values[i][2]; ++j) {
            for (int k = sub_matrix_array.values[i][1]; k <= sub_matrix_array.values[i][3]; ++k) {
                main_matrix.values[j][k] += 1;
            }
        }
    }
}

int getCountNeighbour(matrix m, int i, int j) {
    int i_plus = i + 1, i_minus = i - 1, j_plus = j + 1, j_minus = j - 1, sum = 0;

    i_minus = i_minus < 0 ? m.nRows - 1 : i_minus;
    j_minus = j_minus < 0 ? m.nCols - 1 : j_minus;
    i_plus = i_plus < m.nRows ? i_plus : 0;
    j_plus = j_plus < m.nRows ? j_plus : 0;

    sum += m.values[i_minus][j];
    sum += m.values[i_plus][j];
    sum += m.values[i_minus][j_minus];
    sum += m.values[i_plus][j_minus];
    sum += m.values[i_minus][j_plus];
    sum += m.values[i_plus][j_plus];
    sum += m.values[i][j_minus];
    sum += m.values[i][j_plus];


    return sum;
}

void lifeGameStep(matrix m) {
    matrix buf = getMemMatrix(m.nRows, m.nCols);

    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            buf.values[i][j] = getCountNeighbour(m, i, j);
        }
    }

    outputMatrix(buf);

    for (int i = 0; i < m.nRows; ++i) {
        for (int j = 0; j < m.nCols; ++j) {
            if (buf.values[i][j] < 2) {
                m.values[i][j] = 0;
            } else if (buf.values[i][j] == 3 && m.values[i][j] == 0) {
                m.values[i][j] = 1;
            } else if (buf.values[i][j] > 3 && m.values[i][j] == 1) {
                m.values[i][j] = 0;
            }
        }
    }
    freeMemMatrix(&buf);
}


int compare(const void *a, const void *b) {
    return (*(int *) a - *(int *) b);
}


void medianFilter3(matrix m) {
    int size = 0;
    int a[9];

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i != 1 | j != 1) {
                a[size++] = m.values[i][j];
            }
        }
    }
    qsort(a, size, sizeof(int), compare);
    outputArray_(a, 8);
    m.values[1][1] = a[size / 2];
}


typedef struct Domain {
    char *way;
    int count_used;
} Domain;

Domain *getMemDomainArray(int n) {
    Domain *values = (Domain *) malloc(n * sizeof(Domain));
    return values;
}

Domain getDomain(char *s) {
    Domain domain;
    WordDescriptor word;

    getWordReverse(getEndOfString(s), s, &word);

    domain.count_used = atoi(s);
    domain.way = word.begin;

    return domain;
}

void addSubDomainInArray(Domain *res, int *size_res, char *way, int count_used) {
    Domain domain;
    int is_new_domain = 1;

    for (int i = 1; i <= *size_res; ++i) {
        if (!strcmp(res[i].way, way)) {
            res[i].count_used += count_used;
            is_new_domain = 0;
            break;
        }
    }
    if (is_new_domain) {
        (*size_res)++;
        res[*size_res].count_used = count_used;
        res[*size_res].way = way;
    }
}


void addAllDomain(Domain *res, int *size_res, Domain domain) {
    char *ptrRead = getEndOfString(domain.way);

    while (ptrRead > domain.way) {
        if (*ptrRead == '.') {
            addSubDomainInArray(res, size_res, ptrRead, domain.count_used);
        }
        ptrRead--;
    }
    addSubDomainInArray(res, size_res, ptrRead, domain.count_used);
}

int GetCountUnitSubMatrices(matrix m) {
    int sum = 0;
    for (int i = 0; i < m.nRows; ++i) {
        int *nums = (int *) malloc(m.nCols * sizeof(int));
        for (int j = 0; j < m.nCols; ++j) {
            if (m.values[i][j] == 0) {
                nums[j] = 0;
            } else if (j == 0) {
                nums[j] = 1;
            } else {
                nums[j] = nums[j - 1] + 1;
                sum += nums[j - 1] + 1;
            }
            int min = INT_MAX;
            for (int k = j; k < m.nCols; ++k) {
                min = nums[k] < min ? nums[k] : min;
            }
            sum += min;
        }
    }
    return sum;
}

int findMax(int *a, int size) {
    int max = INT64_MIN;
    for (int i = 0; i < size; i++) {
        if (a[i] > max)
            max = a[i];
    }
    return max;
}

int findIndexMax(int *a, int size) {
    int index_max = 0;
    for (int i = 0; i < size; ++i) {
        if (a[i] == findMax(a, size))
            index_max = i;
    }
}

void deleteRightPart(int *a, int size, int max_index) {
    while (max_index <= size) {
        deleteByPosSaveOrder_(a, &size, max_index++);
    }
}

void deleteLeftPart(int *a, int size, int max_index) {
    int i = 0;
    while (i <= max_index) {
        deleteByPosSaveOrder_(a, &size, i++);
    }
}

typedef struct binaryTree_s {
    int data;
    struct binaryTree_s *left;
    struct binaryTree_s *right;
} binaryTree;


binaryTree *createNode(int data) {
    binaryTree *newNode = (binaryTree *) malloc(sizeof(binaryTree));
    if (newNode == NULL) {
        printf("Malloc returned NULL\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void push(binaryTree **tree, int data) {
    binaryTree *newNode = createNode(data);

    binaryTree *tmp = *tree;
    if (tmp == NULL) {
        *tree = newNode;
    } else if (data < tmp->data) {
        if (tmp->left == NULL) {
            tmp->left = createNode(data);
        } else {
            push(&(tmp->left), data);
        }
    } else if (data > tmp->data) {
        if (tmp->right == NULL) {
            tmp->right = createNode(data);
        } else {
            push(&(tmp->right), data);
        }
    }
}

// рекурсивный обход в глубину
void printInDepthRecursively(binaryTree *tree) {
    if (tree == NULL) {
        return;
    } else {
        printf("%d ", tree->data);
        if (tree->left != NULL) {
            printInDepthRecursively(tree->left);
        }
        if (tree->right != NULL) {
            printInDepthRecursively(tree->right);
        }
    }
}

void printBinTree(binaryTree *tree) {
    if (tree != NULL) { //Пока не встретится пустой узел
        printf("%d ", tree->data); //Отображаем корень дерева
        printBinTree(tree->left); //Рекурсивная функция для левого поддерева
        printBinTree(tree->right); //Рекурсивная функция для правого поддерева
    }
}

binaryTree *createTask7BinTree(int *a, int size) {
    int maxParent = findMax(a, size);
    binaryTree *newTree = createNode(maxParent);

    int *bufLeft = a;
    int sizeBufL = size;

    int *bufRight = a;
    int sizeBufR = size;

    int index_max = findIndexMax(a, size);

    deleteRightPart(bufLeft, sizeBufL, index_max);

    while (sizeBufL != 0) {
        int currentMaxIndex = findIndexMax(bufLeft, sizeBufL);
        push(newTree, bufLeft[currentMaxIndex]);
        deleteByPosSaveOrder_(bufLeft, &sizeBufL, currentMaxIndex);
    }

    deleteLeftPart(bufRight, sizeBufR, index_max);

    while (sizeBufR != 0) {
        int currentMaxIndex = findIndexMax(bufRight, sizeBufR);
        push(newTree, bufRight[currentMaxIndex]);
        deleteByPosSaveOrder_(bufRight, &sizeBufR, currentMaxIndex);
    }

    return newTree;
}


char *makeStringFromIndeces(char *s, int *indices, int indicesSize) {
    char *result = (char *) malloc((indicesSize + 1) * sizeof(char));

    for (int i = 0; i < indicesSize; i++)
        result[indices[i]] = s[i];

    result[indicesSize] = '\0';

    return result;
}


void check_Correct_Open_File(FILE *f) {
    if (f == NULL) {
        perror("f");
        exit(1);
    }
}

char *getWayByTasks(char *filename) {
    char *way = __FILE__;
    char *sub_way = str_replace("tasks/F", "F", filename);
    return str_replace(way, __FILE_NAME__, sub_way);
}

void GenerateRandomIntNumbers(FILE *file, int count) {
    srand(time(NULL));
    for (int i = 0; i < count; i++) {
        int number = ((int) rand() / RAND_MAX) * 1000;
        fprintf(file, "d\n", number);
    }
}

void ReadIntNumbers(FILE *file, int numbers[], int *count) {
    *count = 0;
    while (fscanf(file, "%d", &numbers[*count]) == 1)
        (*count)++;
}

void WriteIntNumbers(FILE *file, int numbers[], int count) {
    for (int i = 0; i < count; i++)
        fprintf(file, "%d\n", numbers[i]);
}

