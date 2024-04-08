#include <stdio.h>
#include <stdlib.h>
#include "libs/string_/string_/string_.c"
#include "libs/tests/using_string_.c"
#include "libs/data_structures/matrix/matrix.c"
#include "libs/data_structures/vector/vector.c"
#include <time.h>
#include <math.h>

void check_Correct_Open_File(FILE *f) {
    if (f == NULL) {
        printf("errno %d\n", errno);
        perror("f");
        exit(1);
    }
}


void WriteMatricesBinaryFile(char *file_name, FILE *file, matrix *data, int count_matrices) {
    char *c;
    file = fopen(file_name, "wb");
    check_Correct_Open_File(file);

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
    check_Correct_Open_File(file);

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
    check_Correct_Open_File(file);
    c = (char *) ptr;

    while ((counter = getc(file)) != EOF) {
        *c = counter;
        c++;
    }

    outputMatrices(ptr, count_matrices);
    fclose(file);
    free(ptr);
}

char *getWayByTasks(char *filename) {
    char *way = __FILE__;
    char *sub_way = str_replace("tasks/F", "F", filename);
    return str_replace(way, __FILE_NAME__, sub_way);
}

void GenerateRandomFloatNumbers(FILE *file, int count) {
    for (int i = 0; i < count; i++) {
        double number = ((double) rand() / RAND_MAX) * 1000.0;
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

char generateRandomOperator() {
    char operators[] = {'+', '-', '*', '/'};
    return operators[rand() % 4];
}

void WriteGenerateExpression(FILE *file) {
    srand(time(NULL));

    int num1 = (int) rand() % 9 + 1;
    int num2 = (int) rand() % 9 + 1;
    int num3 = (int) rand() % 9 + 1;

    int operator1 = generateRandomOperator();
    int operator2 = generateRandomOperator();

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


void generateRandomWords(const char *filename) {
    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "w");

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

void printCorrectWords(char *inputFilename, char *outputFilename, char *sequence) {
    char *way_input = getWayByTasks(inputFilename);
    FILE *file_input = fopen(way_input, "r");
    check_Correct_Open_File(file_input);

    char *way_output = getWayByTasks(outputFilename);
    FILE *file_output = fopen(way_output, "w");
    check_Correct_Open_File(file_output);

    char word[MAX_N_WORDS_IN_STRING];

    while (fscanf(file_input, "%s", word) == 1) {
        if (strstr(word, sequence))
            fprintf(file_output, "%s\n", word);
    }

    fclose(file_input);
    fclose(file_output);
}

void generateRandomStrings(char *filename) {
    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "w");
    check_Correct_Open_File(file);

    char alphabet[] = " abcdefg hijklm nopqrst uvwxyz ";
    int alphabet_length = strlen(alphabet);

    srand(time(NULL));

    for (int i = 0; i < MAX_N_WORDS_IN_STRING; i++) {
        char word[50];
        int word_length = rand() % (40) + 1;

        for (int j = 0; j < word_length; j++) {
            word[j] = alphabet[rand() % alphabet_length];
        }

        word[word_length] = '\0';
        fprintf(file, "%s\n", word);
    }

    fclose(file);
}

void printMaxLenWordsInString(char *inputFilename, char *outputFilename) {
    char *way_input = getWayByTasks(inputFilename);
    FILE *file_input = fopen(way_input, "r");
    check_Correct_Open_File(file_input);

    char *way_output = getWayByTasks(outputFilename);
    FILE *file_output = fopen(way_output, "w");
    check_Correct_Open_File(file_output);

    char s[50];
    while (fgets(s, 50, file_input)) {
        char *begin_search = s;
        char res[50];
        int max_len = 1;
        WordDescriptor word;

        while (getWord(begin_search, &word)) {
            if ((word.end - word.begin + 1) >= max_len) {
                wordDescriptorToString(word, res);
                max_len = (word.end - word.begin + 1);
            }
            begin_search = word.end;
        }
        fprintf(file_output, "%s\n", res);
    }

    fclose(file_input);
    fclose(file_output);
}

void task5() {
    generateRandomStrings("task5input.txt");
    printMaxLenWordsInString("task5input.txt", "task5output.txt");
}

typedef struct Polinomial {
    int pow;
    int k;
} Polinomial;


void freePolinomial(Polinomial **array, int nPalinom) {
    for (int i = 0; i < nPalinom; i++) {
        free(array[i]);
    }
    free(array);
}


int generateRandomSign() {
    return rand() % 2 == 0 ? 1 : -1;
}

Polinomial **getMemPalinomeKiller(int nPalinomial, int nMember) {
    Polinomial **array = (Polinomial **) malloc(nPalinomial * sizeof(Polinomial *));
    for (int i = 0; i < nPalinomial; i++) {
        array[i] = (Polinomial *) malloc(nMember * sizeof(Polinomial));
    }
    return (array);
}

void generatePolinomialArray(char *filename, int nPalinomial, int nMember) {
    srand(time(NULL));
    Polinomial **array = getMemPalinomeKiller(nPalinomial, nMember);

    for (int i = 0; i < nPalinomial; ++i) {
        for (int j = 0; j < nMember; ++j) {
            array[i][j].pow = j;
            array[i][j].k = generateRandomSign() * rand() % 9 + 1;
        }
    }

    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "wb");
    check_Correct_Open_File(file);

    char *c = (char *) array;
    for (int i = 0; i < sizeof(Polinomial) * nPalinomial * nMember * 2; i++) {
        putc(*c++, file);
    }
    fclose(file);
    freePolinomial(array, nPalinomial);
}


void printCorrectPalinomial(char *filename, int x, int nPalinomial, int nMember) {
    char *c;
    int counter;
    Polinomial **array = getMemPalinomeKiller(nPalinomial, nMember);
    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "rb");
    check_Correct_Open_File(file);
    c = (char *) array;

    while ((counter = getc(file)) != EOF) {
        *c = counter;
        c++;
    }
    fclose(file);

    for (int i = 0; i < nPalinomial; ++i) {
        int res = 0;
        for (int j = 0; j < nMember; ++j) {
            res += (int) pow(x, array[i][j].pow) * array[i][j].k;

        }
        if (res == 0) {
            for (int j = 0; j < nMember; ++j) {
                array[i][j].pow = 000;
                array[i][j].k = 000;
            }
        }
    }

    file = fopen(way, "wb");
    check_Correct_Open_File(file);
    c = (char *) array;
    for (int i = 0; i < sizeof(Polinomial) * nPalinomial * nMember * 2; i++) {
        putc(*c++, file);
    }
    fclose(file);
    freePolinomial(array, nPalinomial);

}

void printPalinomialWithFile(char *filename, int nPalinomial, int nMember) {
    char *c;
    int counter;
    Polinomial **array = getMemPalinomeKiller(nPalinomial, nMember);
    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "rb");
    check_Correct_Open_File(file);
    c = (char *) array;

    while ((counter = getc(file)) != EOF) {
        *c = counter;
        c++;
    }
    fclose(file);

    for (int i = 0; i < nPalinomial; ++i) {
        int res = 0;
        for (int j = 0; j < nMember; ++j) {
            printf("(%dx^%d)", array[i][j].k, array[i][j].pow);
            if (j != nMember - 1) {
                printf(" + ");
            }

        }
        printf("= 0\n");
    }
    printf("\n");

    freePolinomial(array, nPalinomial);
}

void generateArray(int *a, int size) {
    srand(time(NULL));

    int half = size / 2;
    int counter_positive = 0, counter_negative = 0, index = 0;

    while (counter_negative < half && counter_positive < half) {
        int random_num = generateRandomSign() * (rand() % 100 + 1);
        a[index++] = random_num;

        if (random_num > 0) {
            counter_positive++;
        } else {
            counter_negative++;
        }
    }

    while (counter_negative < half) {
        int random_num = -1 * (rand() % 100 + 1);
        a[index++] = random_num;
        counter_negative++;
    }

    while (counter_positive < half) {
        int random_num = rand() % 100 + 1;
        a[index++] = random_num;
        counter_positive++;
    }
}

void generateArrayBinaryFile(char *filename, int *a, int size) {
    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "wb");
    char *c = (char *) a;
    for (int i = 0; i < sizeof(int) * size; i++) {
        putc(*c++, file);
    }
    fclose(file);
}


void sortArrayInFile(char *filename, int size) {
    int counter;
    int a[size];
    char *c = (char *) a;

    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "rb");

    while ((counter = getc(file)) != EOF) {
        *c = counter;
        c++;
    }
    fclose(file);

    int res[size];
    int positive_index = 0;
    int negative_index = size / 2;
    int index_no_sort_arr = 0;

    while (index_no_sort_arr < size) {
        if (a[index_no_sort_arr] > 0)
            res[positive_index++] = a[index_no_sort_arr++];
        else
            res[negative_index++] = a[index_no_sort_arr++];
    }

    generateArrayBinaryFile(filename, res, size);
}

void outputArrayFromFile(char *filename, int size) {
    int counter;
    int a[size];
    char *c = (char *) a;

    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "rb");

    while ((counter = getc(file)) != EOF) {
        *c = counter;
        c++;
    }
    fclose(file);
    outputArray_(a, size);
}


void transpocseMatrixIfNotSymetricFile(char *file_name, FILE *file, int count_matrices) {
    char *c;
    int counter;
    int size = sizeof(matrix) * count_matrices;
    matrix *ptr = malloc(size);
    file = fopen(file_name, "rb");
    check_Correct_Open_File(file);
    c = (char *) ptr;

    while ((counter = getc(file)) != EOF) {
        *c = counter;
        c++;
    }

    for (int j = 0; j < count_matrices; ++j)
        if (isSymmetricMatrix(&ptr[j]))
            transposeMatrix(&ptr[j]);

    c = (char *) ptr;
    for (int i = 0; i < sizeof(matrix) * count_matrices; i++)
        putc(*c++, file);

    fclose(file);
    free(ptr);
}


typedef struct Sportsman {
    char *name;
    char *surname;
    int res;
} Sportsman;

Sportsman *getMemForSportsmensArray(int nSportsmens) {
    Sportsman *array_sportsmens = (Sportsman *) malloc(nSportsmens * sizeof(Sportsman));
    return array_sportsmens;
}

void genereteSportsmens(Sportsman *array_sportsmens, int count_sportsmens) {
    srand(time(NULL));
    char *names[10] = {"Biba", "Boba", "Linus", "Ryan", "Ryzen", "Bubuntu", \
    "Andrusha", "Women", "Gojo", "Roronoa"};
    char *surnames[10] = {"Otcovich", "Kachkovich", "Kalich", "Torvalds", "ByeByevich", \
    "Archich", "Applich", "Ymich", "Potnich", "Bigsmokevich"};

    for (int i = 0; i < count_sportsmens; ++i) {
        array_sportsmens[i].res = rand() % 100 + 1;
        array_sportsmens[i].name = names[rand() % 10];
        array_sportsmens[i].surname = surnames[rand() % 10];
    }
}

void writeSportsmensInFile(FILE *filename, Sportsman *array_sportsmens, int count_sportsmens) {
    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "wb");

    char *c = (char *) array_sportsmens;

    for (int i = 0; i < sizeof(Sportsman) * count_sportsmens; i++) {
        putc(*c++, file);
    }
    fclose(file);
}

void outputSportsmensFromFile(char *filename, int nSportsmens) {
    int counter;
    Sportsman *array_sportsmens = getMemForSportsmensArray(nSportsmens);
    char *c = (char *) array_sportsmens;

    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "rb");

    while ((counter = getc(file)) != EOF) {
        *c = counter;
        c++;
    }
    fclose(file);

    for (int i = 0; i < nSportsmens; ++i) {
        printf("%s %s--->%d\n", array_sportsmens[i].name, array_sportsmens[i].surname, array_sportsmens[i].res);
    }
}

int compareSportsmens(Sportsman a, Sportsman b) {
    return b.res - a.res;
}

void getBestTeam(FILE *filename, int size_team, int count_sportsmens) {
    int counter;
    Sportsman *team = getMemForSportsmensArray(size_team);
    Sportsman *array_sportsmens = getMemForSportsmensArray(count_sportsmens);

    char *c = (char *) array_sportsmens;
    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "rb");

    while ((counter = getc(file)) != EOF) {
        *c = counter;
        c++;
    }
    fclose(file);


    qsort(array_sportsmens, count_sportsmens, sizeof(Sportsman),
          (int (*)(const void *, const void *)) compareSportsmens);

    for (int i = 0; i < size_team; ++i) {
        team[i] = array_sportsmens[i];
    }

    writeSportsmensInFile(filename, team, size_team);
    outputSportsmensFromFile(filename, size_team);
}

typedef struct Product {
    char *name;
    int price;
    int count;
    int full_price;
} Product;

Product *getMemForProductArray(int nProduct) {
    Product *array_product = (Product *) calloc(nProduct, sizeof(Product));
    return array_product;
}

void generateProductArray(Product *array_product) {
    srand(time(NULL));
    char *names[] = {"Banans", "Apples", "Lays", "Muka", "Water", "Ryzen5500", "RTX4090"};
    int count_unique_product = 0;
    for (int i = 0; i < 7; ++i) {
        array_product[i].name = names[i];
        array_product[i].count = rand() % 20;
        array_product[i].price = rand() %300 + 1;
        array_product[i].full_price = array_product[i].price * array_product[i].count;
    }
}

void generateConsignment(Product *array_product) {
    char *names[] = {"Banans", "Apples", "Lays", "Muka", "Water", "Ryzen5500", "RTX4090"};
    int count_unique_product = 0;
    for (int i = 0; i < 7; ++i) {
        array_product[i].name = names[i];
        array_product[i].count = rand() % 20;
        array_product[i].price = 0;
        array_product[i].full_price = array_product[i].price * array_product[i].count;
    }
}

void outputProducts(Product *array, int count_product) {
    for (int i = 0; i < count_product; ++i) {
        printf("%s\n Price: %d Count: %d\n",array[i].name, array[i].price, array[i].count);
    }
}

void updateBaseProduct(Product *array_product, Product *array_consignment, int count_product) {
    for (int i = 0; i < count_product; ++i) {
        for (int j = 0; j < count_product; ++j) {
            if (!(strcmp(array_consignment[i].name, array_product[j].name))) {
                array_product[j].count = array_product[j].count > array_consignment[i].count ? array_product[j].count - array_consignment[i].count : 0;
                array_product[j].full_price = array_product[j].count * array_product[j].price;
            }
        }
    }
}

void writeProductsInFile(FILE *filename,Product *array_product, int count_product) {
    char *way = getWayByTasks(filename);
    FILE* file = fopen(way, "wb");

    char *c = (char *) array_product;

    for (int i = 0; i < sizeof(Product) * count_product; i++) {
        putc(*c++, file);
    }
    fclose(file);
}

void readProductsInFile(FILE *filename, int count_product) {
    int counter;
    Sportsman *array = getMemForProductArray(count_product);;
    char *c = (char *) array;

    char *way = getWayByTasks(filename);
    FILE *file = fopen(way, "rb");

    while ((counter = getc(file)) != EOF) {
        *c = counter;
        c++;
    }
    fclose(file);
}

