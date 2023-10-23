#include <stdio.h>
#include <stdlib.h>

#include "ppm.h"
#include "cli.h"

int main(int argc, char** argv) {
    CliArgs cli = parse_cli(argc, argv);

    const size_t N = cli.rows;
    const size_t N_COLORS = cli.colors;
    size_t* attractors = malloc(sizeof(size_t) * N);

    for (size_t i = 0; i < N; ++i) {
        attractors[i] = rand() % N_COLORS;
    }

    char* color_scheme = generate_attractor_scheme(N_COLORS);

    FILE* out = fopen("precomputed.ppm", "w");

    for (size_t i = 0; i < N; ++i) {
        fwrite(color_scheme + attractors[i] * 12, sizeof(char), 12, out);
    }

    free(attractors);

    return 0;
}
