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

static inline void vec_add(double* x, double* y, size_t* p, size_t size) {
    double a = 1.5;
    for ( size_t k = 0; k < size; ++k ) {
        size_t j = p[k];
        y[j] += a * x[j];
    }
}

static inline void vec_add_linear(double* x, double* y, size_t size) {
    double a = 1.5;
    for ( size_t i = 0; i < size; ++i ) {
        y[i] += a * x[i];
    }
}

int main() {
    const size_t size = 1000000;
    double* x = malloc(sizeof(double) * size);
    double* y = malloc(sizeof(double) * size);
    size_t* p = malloc(sizeof(size_t) * size);

    for ( size_t i = 0; i < size; ++i ) {
        x[i] = ((double) rand()) / RAND_MAX * 1000;
        y[i] = ((double) rand()) / RAND_MAX * 1000;
    }

    // Dense allocation
    for ( size_t i = 0; i < size; ++i ) {
        p[i] = i;
    }

    printf("\n");
    BENCHMARK(vec_add(x, y, p, size), 1000);
    printf("Time elapsed during dense allocation: %f\n", timeDiff);

    int i = ((double) rand()) / RAND_MAX * 1000;
    printf("%f %f\n", x[i], y[i]);

    // Sparse allocation
    size_t size_jump = 1000;
    for ( size_t j = 0, k = 0; j < size_jump; ++j ) {
        for ( size_t i = j; i < size; i += size_jump, ++k ) {
            p[i] = k;
        }
    }

    BENCHMARK(vec_add(x, y, p, size), 1000);
    printf("Time elapsed during sparse allocation: %f\n", timeDiff);

    i = ((double) rand()) / RAND_MAX * 1000;
    printf("%f %f\n", x[i], y[i]);

    BENCHMARK(vec_add_linear(x, y, size), 1000);
    printf("Time elapsed during linear addition: %f\n", timeDiff);

    i = ((double) rand()) / RAND_MAX * 1000;
    printf("%f %f\n", x[i], y[i]);

    free(x);
    free(y);
    free(p);
}
