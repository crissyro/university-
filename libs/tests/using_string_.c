#include "../string_/string_/string_.c"

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} WordDescriptor;


// 3
int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}


// 4
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



// 5

// 6


// 7



// 8



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



// 19