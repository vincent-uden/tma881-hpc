#define _POSIX_SOURCE

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

    FILE* out = fopen("naive.ppm", "w");
    write_header(out, 10000, 255);

    hsv color_in;
    color_in.s = 1.0;
    color_in.v = 1.0;
    rgb color;
    for (size_t i = 0; i < N; ++i) {
        color_in.h = (360.0 * attractors[i]) / ((float) N_COLORS);
        color = hsv2rgb(color_in);
        fprintf(
            out,
            "%d %d %d\n",
            (int) (color.r * 255),
            (int) (color.g * 255),
            (int) (color.b * 255)
        );
    }

    fclose(out);
    free(attractors);

    return 0;
}
