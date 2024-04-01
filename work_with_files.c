#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


void check_Correct_Open_File(FILE *f) {
    if (f == NULL) {
        printf("errno %d\n", errno);
        perror("f");
        exit(1);
    }
}

// task 1



int main() {


    return 0;
}