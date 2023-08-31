#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char** argv) {
    char* A = NULL;
    char* B = NULL;

    int c = -1;
    while ((c = getopt(argc, argv, "a:b:")) != -1) {
        switch (c) {
        case 'a':
            A = optarg;
            break;
        case 'b':
            B = optarg;
            break;
        default:
            fprintf(stderr, "Usage: %s -a A -b B \n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (A != NULL && B != NULL) {
        char* endptr = NULL;
        int success = 1;
        errno = 0;
        int a = strtol(A, &endptr, 0);
        if (errno != 0 || endptr == A) {
            fprintf(stderr, "A must be an integer\n");
            success = 0;
        }
        errno = 0;
        endptr = NULL;
        int b = strtol(B, &endptr, 0);
        if (errno != 0 || endptr == B) {
            fprintf(stderr, "B must be an integer\n");
            success = 0;
        }

        if (success) {
            printf("A is %d and B is %d\n", a, b);
        }
    } else {
        fprintf(stderr, "Usage: %s -a A -b B \n", argv[0]);
        exit(EXIT_FAILURE);
    }
}
