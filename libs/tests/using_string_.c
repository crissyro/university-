#include "../string_/string_/string_.c"
#include <string.h>
#include <malloc.h>


char *getEndOfString(char *source) {
    char *end = source;
    while (*end) {
        end++;
    }
    return end;
}

// 1 удалить из строки все пробельные символы
void removeNonLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}


// 2 Сократить количество пробелов между словами данного предложения до
//одного

void removeExtraSpaces(char *s) {
    char *src = s;
    char *dst = s;
    int spaceCount = 0;

    while (*src) {
        if (*src == ' ') {
            spaceCount++;
            if (spaceCount <= 1) {
                *dst = *src;
                dst++;
            }
        } else {
            *dst = *src;
            dst++;
            spaceCount = 0;
        }
        src++;
    }
    *dst = '\0';
}

// 3  преобразовать строку таким образом, чтобы цифры
//каждого слова были перенесены в начало слова и изменить порядок следования
//цифр в слове на обратный, а буквы – в конец слова, без изменения порядка
//следования

int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}

void digitToStartWord(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,
                                 _stringBuffer);
    char *recPosition = copyIfReverse(endStringBuffer - 1,
                                      _stringBuffer - 1,
                                      word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}

void digitToStart(char *beginString) {
    char *beginSearch = beginString;
    WordDescriptor word;
    while (getWord(beginSearch, &word)) {
        digitToStartWord(word);
        beginSearch = word.end;
    }

}

// 4 Преобразовать строку, заменяя каждую цифру соответствующим ей числом
//пробелов.
void replace_Digits_With_Spaces(char *input) {
    char buffer[MAX_STRING_SIZE];
    int buffer_index = 0;
    for (int i = 0; i < strlen_(input); i++) {
        if (isdigit(input[i])) {
            int num_spaces = input[i] - '0';
            for (int j = 0; j < num_spaces; j++) {
                buffer[buffer_index++] = ' ';
            }
        } else
            buffer[buffer_index++] = input[i];
    }
    buffer[buffer_index] = '\0';

    printf("%s\n", buffer);
}



// 5 Заменить все вхождения слова 𝑤1 на слово 𝑤2

void replace(char *source, char *w1, char *w2) {
    size_t w1_size = strlen_(w1);
    size_t w2_size = strlen_(w2);
    WordDescriptor word1 = {w1, w1 + w1_size};
    WordDescriptor word2 = {w2, w2 + w2_size};
    char *read_p, *rec_p;
    if (w1_size >= w2_size) {
        read_p = source;
        rec_p = source;
    } else {
        copy(source, getEndOfString(source), _stringBuffer);
        read_p = _stringBuffer;
        rec_p = source;
    }
    while (*read_p != '\0') {
        if (strncmp(read_p, word1.begin, w1_size) == 0) {
            copy(word2.begin, word2.end, rec_p);
            read_p += w1_size;
            rec_p += w2_size;
        } else {
            *rec_p = *read_p;
            read_p++;
            rec_p++;
        }
    }
    *rec_p = '\0';
}

// 6 Определить,
// упорядочены ли лексикографически слова данного предложения.


// 7 Вывести слова данной строки в
// обратном порядке по одному в строке экрана



// 8 В данной строке соседние слова разделены запятыми.
// Определить количество слов-палиндромов.



// 9 Даны две строки. Получить строку, в которой чередуются слова
// первой и второй строки. Если в одной из строк число слов больше,
// чем в другой, то оставшиеся слова этой строки
// должны быть дописаны в строку-результат



// 10 Преобразовать строку,
// изменив порядок следования слов в строке на обратный

char *functionConvert(const char *s) {
    int size = strlen_(s);
    char *temp = malloc(size);
    int t_size = size--;

    for (int i = 0; i < size; i++)
        temp[i] = s[t_size-i];

    return temp;
}


// 11 Вывести слово данной строки, предшествующее первому из слов,
// содержащих букву "а".

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s, WordDescriptor *w) {

}


// 12 Даны две строки. Определить последнее из слов первой строки,
// которое есть во второй строке.



// 13 Определить, есть ли в данной строке одинаковые слова.



// 14 Определить, есть ли в данной строке пара слов,
// составленных из одинакового набора букв.



// 15 Получить строку из слов данной строки,
// которые отличны от последнего слова



// 16 Даны две строки 𝑠1 и 𝑠2. Пусть 𝑤 – первое из слов строки 𝑠1,
// которое есть и в строке 𝑠2.
// Найти слово, предшествующее первому вхождению 𝑤 в 𝑠1



// 17



// 18 Даны две строки. Пусть 𝑛1 – число слов в первой строке,
//// а 𝑛2 – во второй. Требуется дополнить строку,
//// содержащую меньшее количество слов, последними
////словами строки, в которой содержится большее количество слов



// 19 Определить, входит ли в
// данную строку каждая буква данного слова