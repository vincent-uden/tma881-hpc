#ifndef PPM
#define PPM

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
} hsv;

rgb hsv2rgb(hsv in);

char* generate_attractor_scheme(size_t n_colors);

void write_header(FILE* fp, int dims, int color_max);
void write_row(FILE* fp, size_t color_index, char* scheme);

#endif
