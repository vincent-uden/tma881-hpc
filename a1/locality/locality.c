#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

void row_sums(
  double * sums,
  const double ** matrix,
  size_t nrs,
  size_t ncs
) {
  for ( size_t ix = 0; ix < nrs; ++ix ) {
    double sum = 0.;
    for ( size_t jx = 0; jx < ncs; ++jx ) {
      sum += matrix[ix][jx];
    }
    sums[ix] = sum;
  }
}

void row_sums_fast(
  double * sums,
  const double ** matrix,
  size_t nrs,
  size_t ncs
) {
    for ( size_t ix = 0; ix < nrs; ++ix ) {
        sums[ix] = 0.0;
        for ( size_t jx = 0; jx < ncs; ++jx ) {
            sums[ix] += matrix[ix][jx];
        }
    }
}

void col_sums(
  double * sums,
  const double ** matrix,
  size_t nrs,
  size_t ncs
) {
  for ( size_t jx = 0; jx < ncs; ++jx ) {
    double sum = 0.;
    for ( size_t ix = 0; ix < nrs; ++ix ) {
      sum += matrix[ix][jx];
    }
    sums[jx] = sum;
  }
}

// col_sums is the slower of the two
void col_sums_fast(
  double * sums,
  const double ** matrix,
  size_t nrs,
  size_t ncs
) {
    for ( size_t j = 0; j < ncs; ++j ) {
        sums[j] = 0.0;
    }

    for ( size_t i = 0; i < nrs; ++i ) {
        for ( size_t j = 0; j < ncs; ++j ) {
            sums[j] += matrix[i][j];
        }
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
    double colS[1000];
    double colS2[1000];

    struct timespec startTime;
    struct timespec endTime;
    double timeDiff;

    int BENCH_ITER = 5000;

    timespec_get(&startTime, TIME_UTC);
    for (int i = 0; i < BENCH_ITER; ++i) {
        row_sums(rowS, (const double**) matrix, 1000, 1000);
    }
    timespec_get(&endTime, TIME_UTC);
    timeDiff = difftime(endTime.tv_sec, startTime.tv_sec) + (endTime.tv_nsec - startTime.tv_nsec) / 1e9;
    printf("\nTime elapsed computing row sums: %f\n", timeDiff);

    int i = ((double) rand()) / RAND_MAX * 1000;
    printf("%f %f\n", rowS[i], colS[i]);

    timespec_get(&startTime, TIME_UTC);
    for (int i = 0; i < BENCH_ITER; ++i) {
        col_sums(colS, (const double**) matrix, 1000, 1000);
    }
    timespec_get(&endTime, TIME_UTC);
    timeDiff = difftime(endTime.tv_sec, startTime.tv_sec) + (endTime.tv_nsec - startTime.tv_nsec) / 1e9;
    printf("Time elapsed computing col sums: %f\n", timeDiff);

    i = ((double) rand()) / RAND_MAX * 1000;
    printf("%f %f\n", rowS[i], colS[i]);

    timespec_get(&startTime, TIME_UTC);
    for (int i = 0; i < BENCH_ITER; ++i) {
        row_sums_fast(rowS2, (const double**) matrix, 1000, 1000);
    }
    timespec_get(&endTime, TIME_UTC);
    timeDiff = difftime(endTime.tv_sec, startTime.tv_sec) + (endTime.tv_nsec - startTime.tv_nsec) / 1e9;
    printf("Time elapsed computing fast row sums: %f\n", timeDiff);

    i = ((double) rand()) / RAND_MAX * 1000;
    printf("%f %f\n", rowS[i], colS[i]);

    timespec_get(&startTime, TIME_UTC);
    for (int i = 0; i < BENCH_ITER; ++i) {
        col_sums_fast(colS2, (const double**) matrix, 1000, 1000);
    }
    timespec_get(&endTime, TIME_UTC);
    timeDiff = difftime(endTime.tv_sec, startTime.tv_sec) + (endTime.tv_nsec - startTime.tv_nsec) / 1e9;
    printf("Time elapsed computing fast col sums: %f\n", timeDiff);

    i = ((double) rand()) / RAND_MAX * 1000;
    printf("%f %f\n", rowS[i], colS[i]);

    printf("Validating fast alternatives\n");
    for ( size_t i = 0; i < 1000; ++i ) {
        assert(rowS[i] == rowS2[i]);
        assert(colS[i] == colS2[i]);
    }
    printf("Validation Successful!\n");

}
