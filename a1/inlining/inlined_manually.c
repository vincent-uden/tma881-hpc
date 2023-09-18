// gcc inlined_manually.c -O2 -o manual.out
// time ./manual.out
// ./manual.out  3,99s user 0,01s system 99% cpu 4,022 total

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int N = 30000;
    double as_re[N];
    double as_im[N];
    double bs_re[N];
    double bs_im[N];
    double cs_re[N];
    double cs_im[N];

    srand(time(NULL));

    for (int i = 0; i < N; ++i) {
        bs_re[i] = ((double) rand()) / RAND_MAX;
        bs_im[i] = ((double) rand()) / RAND_MAX;
        cs_re[i] = ((double) rand()) / RAND_MAX;
        cs_im[i] = ((double) rand()) / RAND_MAX;
    }

    for (int j = 0; j < 200000; ++j) {
        for (int i = 0; i < N; ++i) {
            as_re[i] = (bs_re[i])*(cs_re[i]) - (bs_im[i])*(cs_im[i]);
            as_im[i] = (as_re[i])*(bs_im[i]) + (as_im[i])*(bs_re[i]);
        }
    }

    int i = ((double) rand()) / RAND_MAX * N;
    printf("%f %f\n", as_re[i], as_im[i]);
}
