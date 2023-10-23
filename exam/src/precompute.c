#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ppm.h"
#include "cli.h"

int main(int argc, char** argv) {
    CliArgs cli = parse_cli(argc, argv);

    const size_t N = cli.rows;
    const size_t N_COLORS = cli.colors;
    size_t* attractors = malloc(sizeof(size_t) * N);

    size_t buf_size = 128;
    char* buffer = malloc(12 * buf_size);

    for (size_t i = 0; i < N; ++i) {
        attractors[i] = rand() % N_COLORS;
    }

    char* color_scheme = generate_attractor_scheme(N_COLORS);

    FILE* out = fopen("precomputed.ppm", "w");

    for (size_t i = 0; i < N; ++i) {
        memcpy(buffer + 12 * (i % buf_size), color_scheme + attractors[i] * 12, 12);
        if ((i + 1) % buf_size == 0) {
            fwrite(buffer, sizeof(char), 12 * buf_size, out);
        }
    }

    free(attractors);

    return 0;
}
