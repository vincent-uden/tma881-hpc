#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main() {
    const int SIZE = 10;

    // Contiguous memory allocation since all rows are of equal size.
    // This allows us to write the entire matrix in binary to a file at once.
    //
    // If we were writing into text form, it wouldn't matter as much for code
    // ergonomics since we'd still need to loop over all elements to convert
    // them to string representation
    int mat[SIZE * SIZE];
    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; ++j) {
        mat[j + i * SIZE] = i * j;
      }
    }

    FILE *fp = fopen("./build/matrix", "w");
    fwrite(mat, sizeof(int), SIZE*SIZE, fp);
    fclose(fp);

    fp = fopen("./build/matrix", "r");
    int mat2[SIZE*SIZE];
    fread(mat2, sizeof(int), SIZE*SIZE, fp);
    fclose(fp);

    for ( int i = 0; i < SIZE; ++i ) {
        for ( int j = 0; j < SIZE; ++j ) {
            assert(mat[j + i * SIZE] == mat2[j + i * SIZE]);
        }
    }

    printf("All assertions passed!\n");
}
