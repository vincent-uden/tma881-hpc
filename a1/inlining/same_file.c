// gcc same_file.c -O2 -o same.out
// time ./same.out
// ./same.out  4,05s user 0,00s system 99% cpu 4,056 total

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void mul_cpx(
    double* a_re,
    double* a_im,
    double* b_re,
    double* b_im,
    double* c_re,
    double* c_im
);


void mul_cpx(
    double* a_re,
    double* a_im,
    double* b_re,
    double* b_im,
    double* c_re,
    double* c_im
) {
    *a_re = (*b_re)*(*c_re) - (*b_im)*(*c_im);
    *a_im = (*a_re)*(*b_im) + (*a_im)*(*b_re);
}

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
            mul_cpx(
                as_re + i,
                as_im + i,
                bs_re + i,
                bs_im + i,
                cs_re + i,
                cs_im + i
            );
        }
    }

    int i = ((double) rand()) / RAND_MAX * N;
    printf("%f %f\n", as_re[i], as_im[i]);
}
