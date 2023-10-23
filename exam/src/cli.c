#include "cli.h"


CliArgs parse_cli(int argc, char** argv) {
    CliArgs args;

    // Default values
    args.rows = 1000;
    args.colors = 5;

    int c;
    int opt_index = 0;

    static struct option long_options[] = {
        // long_name , ?argument required, flag, short_name
        {"rows", required_argument, 0, 'r'},
        {"colors", required_argument, 0, 'c'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((c = getopt_long(argc, argv, "r:c:h", long_options, &opt_index)) != -1) {
        switch (c) {
            case 'r':
                args.rows = atoi(optarg);
                break;
            case 'c':
                args.colors = atoi(optarg);
                break;
            case 'h':
                printf("Usage: newton [OPTIONS]\n");
                printf("Computes how complex plane points converge to function roots.\n");
                printf("\n");
                printf("Options:\n");
                printf("    -r, --rows <rows>     Specify the number of rows to write\n");
                printf("    -c, --colors <colors> Specify the number of colors in the color scheme\n");
                printf("    -h, --help            Display this help message\n");
                printf("\n");
                printf("Description:\n");
                printf("    This program dumps <rows> random pixels of <colors> different colors to a .ppm file at ./naive.ppm\n");
                printf("\n");
                printf("Example usage:\n");
                printf("    out -r 10000 -c 5\n");
                exit(0);
                break;
        }
    }

    return args;
}
