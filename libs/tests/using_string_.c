#include "../string_/string_/string_.c"
#include "../data_structures/bitset/bitset.c"
#include <string.h>

#define COUNT_LETTERS 26
#define DIFFERENCE_CHAR 65

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
void getBagOfWords(BagOfWords *bag, char *s) {
    char *readPtr = s;
    WordDescriptor word;
    for (int i = 0; getWord(readPtr, &word); i++) {
        bag->words[i].begin = word.begin;
        bag->words[i].end = word.end;
        bag->size = i;
    }

}

// 8 В данной строке соседние слова разделены запятыми.
// Определить количество слов-палиндромов.
int isPakindromeWorld(WordDescriptor *word) {
    int word_len = word->end - word->begin;
    for (int i = 0; i < word_len/2; ++i) {
        if ( *(word->begin + i) != *(word->end - i - 1) ) {
            return 0;
        }
    }
    return 1;
}

int GetCountPalindromesInString(char *s) {
    replace(s, ",", " ");
    WordDescriptor word;
    char *BeginWord = s;
    int counter = 0;

    while (getWord(BeginWord,&word)) {
        if (isPakindromeWorld(&word)) {
            counter++;
        }
        BeginWord = word.end;
    }
    return  counter;
}
// 9 Даны две строки. Получить строку, в которой чередуются слова
// первой и второй строки. Если в одной из строк число слов больше,
// чем в другой, то оставшиеся слова этой строки
// должны быть дописаны в строку-результат
void *get_String_From2(char *s1, char *s2, char *res) {
    WordDescriptor word1, word2;
    int is_w1, is_w2;
    char *begin_1 = s1, *begin_2= s2;
    char* write_p = res;

    while ((is_w1 = getWord(begin_1, &word1)), (is_w2 = getWord(begin_2, &word2)), is_w1 || is_w2) {
        if (is_w1) {
            write_p = copy(word1.begin, word1.end, write_p);
            *write_p++ = ' ';
            begin_1 = word1.end;
        }

        if (is_w2) {
            write_p = copy(word2.begin, word2.end, write_p);;
            *write_p++ = ' ';
            begin_2 = word2.end;
        }
    }
    *(--write_p) = '\0';
}

// 10 Преобразовать строку,
// изменив порядок следования слов в строке на обратный
int getWordReverse(char *rbegin, char *rend, WordDescriptor *word) {
    word->end = findNonSpaceReverse(rbegin, rend);
    if (word->end == rend)
        return 0;
    word->begin = findSpaceReverse(rbegin- 1, rend);

    return 1;
}

void getStringRevers(char *s) {
    WordDescriptor word;

    char *write_p = s;
    char *rend = _stringBuffer;
    char *r_begin = copy(s, getEndOfString(s) + 1, _stringBuffer);


    while (getWordReverse(r_begin, rend, &word)) {
        write_p = copy(word.begin, word.end, write_p);
        r_begin = word.begin;
        *write_p++ = ' ';
    }
    *(--write_p) = '\0';
    replace(s, "  ", " ");
}
// 11 Вывести слово данной строки, предшествующее первому из слов,
// содержащих букву "а".

int SymbolIn(char *begin, char *end, int ch) {
    while (begin != end && (toupper(*begin)) != toupper(ch))
        begin++;
    return begin != end;
}

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s, WordDescriptor *w) {
    int isWordInString = getWord(s, w) == 1;

    if (isWordInString && !SymbolIn(w->begin, w->end, 'a')) {
        WordDescriptor copy_w;
        if (getWord(w->end, &copy_w) == 1) {
            if (SymbolIn(copy_w.begin, copy_w.end, 'a'))
                return WORD_FOUND;
            else
                return getWordBeforeFirstWordWithA(w->end, w);

        } else
            return NOT_FOUND_A_WORD_WITH_A;

    } else if (isWordInString)
        return FIRST_WORD_WITH_A;
    else
        return EMPTY_STRING;
}

// 12 Даны две строки. Определить последнее из слов первой строки,
// которое есть во второй строке.
void wordDescriptorToString(WordDescriptor word,char *string) {
    char *end = copy(word.begin, word.end, string);
    *end = '\0';
}


WordDescriptor lastWordInFirstStringInSecondString(char *s1, char *s2) {
    getBagOfWords(&_bag,s1 );
    getBagOfWords(&_bag2,s2 );
    for (int i = 0; i < _bag.size; ++i) {
        WordDescriptor word1 = _bag.words[_bag.size - i - 1];
        for (int j = 0; j < _bag2.size; ++j) {
            WordDescriptor word2 = _bag2.words[j];
            if (!strncmp(word1.begin, word2.begin,word1.end - word1.begin ))
                return _bag.words[_bag.size - i - 1];
        }
    }
    WordDescriptor res;
    char *res_s = "EMPTY";
    getWord(res_s, &res);
    return res;
}


// 13 Определить, есть ли в данной строке одинаковые слова.
int UniqueWordsInString(char *s) {
    BagOfWords bag;
    getBagOfWords(&bag, s);
    for (int i = 0; i < bag.size; ++i) {
        for (int j = i + 1; j < bag.size; ++j) {
            int size_word_1 = bag.words[i].end - bag.words[i].begin;
            int size_word_2 = bag.words[j].end - bag.words[j].begin;
            int max_size_words = size_word_1 > size_word_2 ? size_word_1 : size_word_2;
            if (!strncmp(bag.words[i].begin, bag.words[j].begin, max_size_words))
                return 0;
        }
    }
    return 1;
}


// 14 Определить, есть ли в данной строке пара слов,
// составленных из одинакового набора букв.
int compare_char(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

int checkWordsInStringHaveCommonLetters(char *s) {
    getBagOfWords(&_bag, s);
    for (int i = 0; i < _bag.size; ++i) {
        WordDescriptor word = _bag.words[i];
        qsort(word.begin, word.end - word.begin, sizeof(char), compare_char);
    }
    for (int i = 0; i < _bag.size; ++i) {
        for (int j = i + 1; j < _bag.size; ++j) {
            int size_word_1 = _bag.words[i].end - _bag.words[i].begin;
            int size_word_2 = _bag.words[j].end - _bag.words[j].begin;
            int max_size_words = size_word_1 > size_word_2 ? size_word_1 : size_word_2;

            if (!strncmp(_bag.words[i].begin, _bag.words[j].begin, max_size_words)) {
                return 1;
            }
        }
    }
    return 0;
}

// 15 Получить строку из слов данной строки,
// которые отличны от последнего слова
int getSizeWord(WordDescriptor word) {
    return word.end - word.begin;
}

void GetStringWithoutLastWord(char *s,char *res) {
    char *ptr_w = res;
    getBagOfWords(&_bag,s);
    WordDescriptor last_word = _bag.words[_bag.size - 1];
    int size_last_word  = getSizeWord(last_word);
    for (int i = 0; i < _bag.size - 1; ++i) {
        if (strncmp(_bag.words[i].begin, last_word.begin, size_last_word) != 0) {
            ptr_w = copy(_bag.words[i].begin, _bag.words[i].end, ptr_w);
            *(ptr_w++) = ' ';
        }
    }
    *(--ptr_w) = '\0';
}


// 16 Даны две строки 𝑠1 и 𝑠2. Пусть 𝑤 – первое из слов строки 𝑠1,
// которое есть и в строке 𝑠2.
// Найти слово, предшествующее первому вхождению 𝑤 в 𝑠1
int ThisWordInBag(BagOfWords bag, WordDescriptor word) {
    for (int i = 0; i < bag.size; i++) {
        if (strncmp(word.begin, bag.words[i].begin, getSizeWord(word)) == 0)
            return 1;
    }
    return 0;
}

WordDescriptor GetWordBeforeUnionWord(char *s1, char *s2) {
    getBagOfWords(&_bag, s1);
    getBagOfWords(&_bag2, s2);

    for (int i = 0; i < _bag.size; ++i) {
        if (ThisWordInBag(_bag2, _bag.words[i])) {
            if (i != 0)
                return  _bag.words[i  - 1];
            else
                continue;
        }
    }
    WordDescriptor error_word = {NULL, NULL};
    return error_word;
}


// 17
void DeletePalindromeInString(char *s) {
    char *ptr_w = s;
    char *ptr_r = _stringBuffer;
    copy(s, getEndOfString(s) + 1, ptr_r);
    getBagOfWords(&_bag, ptr_r);
    for (int i = 0; i < _bag.size; ++i) {
        if (!isPakindromeWorld(&_bag.words[i])) {
            ptr_w = copy(_bag.words[i].begin, _bag.words[i].end, ptr_w);
            *(ptr_w++) = ' ';
        }
    }
    *(--ptr_w) = '\0';
}

// 18 Даны две строки. Пусть 𝑛1 – число слов в первой строке,
//// а 𝑛2 – во второй. Требуется дополнить строку,
//// содержащую меньшее количество слов, последними
////словами строки, в которой содержится большее количество слов
void addWordToLessString(char *s1, char *s2) {
    getBagOfWords(&_bag, s1);
    getBagOfWords(&_bag2, s2);
    char *ptr_w;
    int IsString1More = _bag.size > _bag2.size ? 1 : 0;
    size_t difSize = IsString1More ? _bag.size - _bag2.size : _bag2.size - _bag.size;
    if (IsString1More) {
        ptr_w = _bag2.words[_bag2.size - 1].end;
        for (int i = 0; i < difSize; ++i) {
            *(ptr_w++) = ' ';
            ptr_w = copy(_bag.words[_bag2.size + i ].begin, _bag.words[_bag2.size + i].end, \
            ptr_w);
        }
    } else {
        ptr_w = _bag.words[_bag.size - 1].end;
        for (int i = 0; i < difSize; ++i) {
            *(ptr_w++) = ' ';
            ptr_w = copy(_bag2.words[_bag.size + i].begin, _bag2.words[_bag.size + i].end, \
            ptr_w);
        }
    }
    *ptr_w = '\0';
}

// 19 Определить, входит ли в
// данную строку каждая буква данного слова
int allSymbolsWordInString(char *s, char *word) {
    bitset letters_s = bitset_create(COUNT_LETTERS);
    bitset letters_word = bitset_create(COUNT_LETTERS);
    for (int i = 0; i < strlen_(s); ++i) {
        char symbol = toupper(s[i]);
        if (isalpha(symbol))
            bitset_insert(&letters_s, (symbol - DIFFERENCE_CHAR));
    }
    for (int i = 0; i < strlen_(word); ++i) {
        char symbol = toupper(word[i]);
        if (isalpha(symbol))
            bitset_insert(&letters_word, (int) (symbol - DIFFERENCE_CHAR));
    }
    bitset res = bitset_intersection(letters_s, letters_word);
    return bitset_isEqual(res, letters_word);
}

char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}