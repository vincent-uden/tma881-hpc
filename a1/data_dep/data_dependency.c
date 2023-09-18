#include <stdlib.h>
#include <stdio.h>
#include <time.h>

double timeDiff = 0.0f;
struct timespec startTime;
struct timespec endTime;

#define BENCHMARK(func, iters) \
    timespec_get(&startTime, TIME_UTC); \
    for (int i = 0; i < iters; ++i) { \
      func; \
    } \
    timespec_get(&endTime, TIME_UTC); \
    timeDiff = difftime(endTime.tv_sec, startTime.tv_sec) + (endTime.tv_nsec - startTime.tv_nsec) / 1e9; \

void row_sums(
    double * sums,
    const double ** matrix,
    size_t nrs,
    size_t ncs
) {
    for ( size_t ix = 0; ix < nrs; ++ix ) {
        double sum = 0.;
        for ( size_t jx = 0; jx < ncs; ++jx )
            sum += matrix[ix][jx];
        sums[ix] = sum;
    }
}

void row_sums_unrolled2(
    double * sums,
    const double ** matrix,
    size_t nrs,
    size_t ncs
) {
    for ( size_t ix = 0; ix < nrs; ++ix ) {
        double sum0 = 0.;
        double sum1 = 0.;
        for ( size_t jx = 0; jx < ncs; jx += 2 ) {
            sum0 += matrix[ix][jx];
            sum1 += matrix[ix][jx+1];
        }
        sums[ix] = sum0 + sum1;
    }
}

void row_sums_unrolled4(
    double * sums,
    const double ** matrix,
    size_t nrs,
    size_t ncs
) {
    for ( size_t ix = 0; ix < nrs; ++ix ) {
        double sum0 = 0.;
        double sum1 = 0.;
        double sum2 = 0.;
        double sum3 = 0.;
        for ( size_t jx = 0; jx < ncs; jx += 4 ) {
            sum0 += matrix[ix][jx];
            sum1 += matrix[ix][jx+1];
            sum2 += matrix[ix][jx+2];
            sum3 += matrix[ix][jx+3];
        }
        sums[ix] = sum0 + sum1 + sum2 + sum3;
    }
}

void row_sums_unrolled8(
    double * sums,
    const double ** matrix,
    size_t nrs,
    size_t ncs
) {
    for ( size_t ix = 0; ix < nrs; ++ix ) {
        double sum0 = 0.;
        double sum1 = 0.;
        double sum2 = 0.;
        double sum3 = 0.;
        double sum4 = 0.;
        double sum5 = 0.;
        double sum6 = 0.;
        double sum7 = 0.;
        for ( size_t jx = 0; jx < ncs; jx += 8 ) {
            sum0 += matrix[ix][jx];
            sum1 += matrix[ix][jx+1];
            sum2 += matrix[ix][jx+2];
            sum3 += matrix[ix][jx+3];
            sum4 += matrix[ix][jx+4];
            sum5 += matrix[ix][jx+5];
            sum6 += matrix[ix][jx+6];
            sum7 += matrix[ix][jx+7];
        }
        sums[ix] = sum0 + sum1 + sum2 + sum3 + sum4 + sum5 + sum6 + sum7;
    }
}

void row_sums_unrolled4_array(
    double * sums,
    const double ** matrix,
    size_t nrs,
    size_t ncs
) {
    for ( size_t ix = 0; ix < nrs; ++ix ) {
        double sum[4] = { 0., 0., 0., 0. };
        for ( size_t jx = 0; jx < ncs; jx += 4 ) {
            sum[0] += matrix[ix][jx];
            sum[1] += matrix[ix][jx+1];
            sum[2] += matrix[ix][jx+2];
            sum[3] += matrix[ix][jx+3];
        }
        sums[ix] = sum[0] + sum[1] + sum[2] + sum[3];
    }
}

int main() {
    double* data = malloc(sizeof(double) * 1000 * 1000);
    double* matrix[1000];
    srand(time(NULL));
    for (int i = 0; i < 1000 * 1000; ++i) {
        data[i] = ((double) rand()) / RAND_MAX;
    }

    for (int i = 0; i < 1000; ++i) {
        matrix[i] = data + i * 1000;
    };

    double rowS[1000];
    double rowS2[1000];
    double rowS4[1000];
    double rowS8[1000];
    double rowS4_arr[1000];

    printf("\n");
    BENCHMARK(row_sums(rowS, (const double**) matrix, 1000, 1000), 5000)
    printf("Naive       : %f\t", timeDiff);

    BENCHMARK(row_sums_unrolled2(rowS2, (const double**) matrix, 1000, 1000), 5000)
    printf("Unrolled (2): %f\t", timeDiff);

    BENCHMARK(row_sums_unrolled4(rowS4, (const double**) matrix, 1000, 1000), 5000)
    printf("Unrolled (4): %f\t", timeDiff);

    BENCHMARK(row_sums_unrolled8(rowS8, (const double**) matrix, 1000, 1000), 5000)
    printf("Unrolled (8): %f\t", timeDiff);

    BENCHMARK(row_sums_unrolled4_array(rowS4_arr, (const double**) matrix, 1000, 1000), 5000)
    printf("Unrolled (4 array): %f\n", timeDiff);

    int i = ((double) rand()) / RAND_MAX * 1000;
    printf("%f %f %f %f %f \n", rowS[i], rowS2[i], rowS4[i], rowS8[i], rowS4_arr[i]);
}
