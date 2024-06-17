#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define size_t unsigned
#define FALSE 0
#define TRUE 1
#define BUFFER_SIZE 1024

void compare_files(FILE *f1, FILE *f2) {
    char line1[BUFFER_SIZE], line2[BUFFER_SIZE];
    unsigned n=1;

    while (TRUE) {
        if (fgets(line1, BUFFER_SIZE, f1)==NULL) {
            while (fgets(line2, BUFFER_SIZE, f2)){
                fprintf(stdout, "line %u of second file: %s\n", n, line2);
                n++;
            }
            break;
        };
        if (fgets(line2, BUFFER_SIZE, f2)==NULL) {
            while (fgets(line1, BUFFER_SIZE, f1)){
                fprintf(stdout, "line %u of first file: %s\n", n, line1);
                n++;
            }
            break;
        };

        if (strcmp(line1, line2)) {
            fprintf(stdout, "line %u of first file: %s\nline %u of second file: %s\n", n, line1, n, line2);
        }
        n++;
    }

}

int main(int argc, char *argv[]) {
    FILE *src1, *src2;
    if (argc != 3) {
        perror("usage: $0 filename1 filename2");
        exit(EXIT_FAILURE);
    }

    if (!(src1 = fopen(argv[1], "r"))) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    if (!(src2 = fopen(argv[2], "r"))) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    compare_files(src1, src2);

    fclose(src1);
    fclose(src2);

    exit(EXIT_SUCCESS);

}