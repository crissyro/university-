#include "../string_/string_/string_.c"
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

void removeExtraSpaces(char *beginSource, char *endSource, char *beginDestination) {
    while (beginSource != endSource) {
        if (!isspace(*beginSource) || !isspace(*(beginSource + 1))) {
            *beginDestination = *beginSource;
            beginDestination++;
        }
        beginSource++;
    }
    *beginDestination= '\0';
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
char *digitReplaceSpace(char *s, char *prtWrite ) {
    for (int i = 0; i < *s - 48; ++i) {
        *prtWrite = ' ';
        prtWrite++;
    }
    return prtWrite;
}

void digitsReplaceSpace(char *s) {
    char *ptrWrite = s;
    char *ptrRead = _stringBuffer;
    char *endStringBuffer = copy(s, getEndOfString(s) + 1,ptrRead);

    while (ptrRead <= endStringBuffer) {
        if (isdigit(*ptrRead)) {
            ptrWrite = digitReplaceSpace(ptrRead, ptrWrite);
        } else {
            *ptrWrite = *ptrRead;
            ptrWrite++;
        }
        ptrRead++;
    }
    *ptrWrite = '\0';
}



// 5 Заменить все вхождения слова 𝑤1 на слово 𝑤2

int strncmp(const char *str1, const char *str2, size_t n) {
    char *end = str1 + n;
    int result = 0;

    for (; result == 0 && str1 != end && (*str1 || *str2); result = *(str1++) - *(str2++));

    return result;
}

void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);

    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};

    char *readPtr, *recPtr;

    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        copy(source, getEndOfString(source) + 1, _stringBuffer);
        readPtr = _stringBuffer;
        recPtr = source;
    }

    while (*readPtr != '\0') {
        if (strncmp(readPtr, w1, w1Size) == 0) {
            copy(word2.begin, word2.end, recPtr);
            readPtr += w1Size;
            recPtr += w2Size;
        } else {
            *recPtr = *readPtr;
            readPtr++;
            recPtr++;
        }
    }
    *recPtr = '\0';
}

// 6 Определить,
// упорядочены ли лексикографически слова данного предложения.

int is_Sorted_Words(char *s) {
    WordDescriptor w1;
    WordDescriptor w2;
    while (getWord(s,&w1)) {
        if (getWord(w1.end, &w2)) {
               if (*w1.begin > *w2.begin)
                   return 0;
           }
        s = w1.end;
    }
    return 1;
}

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
char *recerse_Words(const char *s) {

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