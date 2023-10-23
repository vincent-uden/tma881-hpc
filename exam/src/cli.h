#ifndef CLI
#define CLI

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

typedef struct {
    size_t rows;
    size_t colors;
} CliArgs;

CliArgs parse_cli(int argc, char** argv);

#endif
