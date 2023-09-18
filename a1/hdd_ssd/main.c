#include <stdio.h>
#include <stdlib.h>
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

void read_and_write_individually(FILE* fp, int* bytes, size_t N) {
    fseek(fp, 0, SEEK_SET);
    for ( int i = 0; i < N; ++i ) {
        fwrite(bytes + i, 1, 1, fp);
        fflush(fp);
    }

    fseek(fp, 0, SEEK_SET);

    for ( int i = 0; i < N; ++i ) {
        fread(bytes + i, 1, 1, fp);
    }
}

void read_and_write_contig(FILE* fp, int* bytes, size_t N) {
    fseek(fp, 0, SEEK_SET);
    fwrite(bytes, 1, N, fp);
    fflush(fp); // Should be unnecessary

    fseek(fp, 0, SEEK_SET);
    fread(bytes, 1, N, fp);
}

int main() {
    const int N = 1 << 20;
    int* bytes = malloc(sizeof(int) * N);

    for ( int i = 0; i < N; ++i ) {
        bytes[i] = i;
    }

    char* HDD_PATH = "./bytes.dat";
    char* SSD_PATH = "/run/mount/scratch/hpcuser156/bytes.dat";

    FILE* hdd = fopen(HDD_PATH, "w+");
    FILE* ssd = fopen(SSD_PATH, "w+");

    if (hdd == NULL) {
        printf("Couldn't open file on HDD at %s\n", HDD_PATH);
    }
    if (ssd == NULL) {
        printf("Couldn't open file on SSD at %s\n", SSD_PATH);
    }

    printf("\n");
    BENCHMARK(read_and_write_individually(hdd, bytes, N), 10);
    printf("HDD Individual w/r: %f\t seconds", timeDiff);

    fclose(hdd);
    fopen(HDD_PATH, "w+");

    printf("\n");
    BENCHMARK(read_and_write_contig(hdd, bytes, N), 10);
    printf("HDD Contiguous w/r: %f\t seconds", timeDiff);

    fclose(hdd);
    fopen(HDD_PATH, "w+");

    printf("\n");
    BENCHMARK(read_and_write_individually(ssd, bytes, N), 10);
    printf("SSD Individual w/r: %f\t seconds", timeDiff);

    fclose(hdd);
    fopen(HDD_PATH, "w+");

    printf("\n");
    BENCHMARK(read_and_write_contig(ssd, bytes, N), 10);
    printf("SSD Contiguous w/r: %f\t seconds", timeDiff);


    free(bytes);
}
