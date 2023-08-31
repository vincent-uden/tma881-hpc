#include <stdio.h>
#include <stdlib.h>


void stackAlloc() {
    // Segfaults at size ~ 10000000 ~ 10MB
    int size = 10000000;

    int as[size];
    for ( int i = 0; i < size; ++i ) {
        as[i] = 0;
    }

    printf("%d\n", as[0]);
}

void heapAlloc() {
    // Doesn't segfault even at 10 times the size of the stack allocation
    int size = 100000000;

    int* as = malloc(sizeof(int) * size);
    for ( int i = 0; i < size; ++i ) {
        as[i] = 0;
    }

    printf("%d\n", as[0]);

    free(as);
}

void contigAlloc() {
    int size = 10;

    // One long unbroken block on the heap
    // Contains all items in the "matrix"
    int* asentries = malloc(sizeof(int) * size*size);
    // Another long unbroken block on the heap
    // Contains pointers to the start of each "row" of the "matrix"
    int** as = malloc(sizeof(int*) * size);

    // Initialize all row pointers
    for ( int i = 0, j = 0; i < size; ++i, j+=size ) {
        // Pointer arithmetic automatically advances the pointer in increments
        // of the size for the data type it is pointing to.
        as[i] = asentries + j;
    }

    // Initialize all items to 0
    for ( int i = 0; i < size; ++i ) {
        for ( int j = 0; j < size; ++j ) {
            as[i][j] = 0;
        }
    }

    printf("%d\n", as[0][0]);
    free(as);
    free(asentries);
}

void fragmentedAlloc() {
    int size = 10;

    // One long unbroken block on the heap
    // Contains pointers to the start of every "row" of the "matrix"
    int** as = malloc(sizeof(int*) * size);
    // Repeatedly allocate one row at a time as discrete "blocks" of memory
    for ( int i = 0; i < size; ++i ) {
        // Other calls to allocate memory from the same or other programs
        // running might occur between each malloc, leading to each row being
        // a contiguous block of memory, but the blocks can be spread out
        // across the RAM.
        as[i] = malloc(sizeof(int) * size);
    }

    // Initialize all items to 0
    for ( int i = 0; i < size; ++i ) {
        for ( int j = 0; j < size; ++j ) {
            as[i][j] = 0;
        }
    }

    printf("%d\n", as[0][0]);

    // All blocks of memory have to be freed individually this time
    for ( int i = 0; i < size; ++i ) {
        free(as[i]);
    }
    free(as);
}


int main() {
    heapAlloc();
    contigAlloc();
    fragmentedAlloc();
}
