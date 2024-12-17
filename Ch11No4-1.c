#include <stdio.h>

#define MAX_ROWS 100
#define MAX_COLS 100

void scan_matrix(const char *filename, int matrix[MAX_ROWS][MAX_COLS], int *rows, int *cols) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open input file");
        return;
    }

    fscanf(file, "%d %d", rows, cols);
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            fscanf(file, "%d", &matrix[i][j]); 
        }
    }
    fclose(file);
}

void write_sparse(const char *filename, int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open output file");
        return;
    }

    int non_zero_count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                non_zero_count++;
            }
        }
    }

    fprintf(file, "%d %d\n", rows, cols);
    fprintf(file, "%d\n", non_zero_count);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                fprintf(file, "%d %d %d\n", i, j, matrix[i][j]);
            }
        }
    }
    fclose(file);
}

int main() {
    int matrix[MAX_ROWS][MAX_COLS];
    int rows, cols;

    const char *input_file = "traditional_matrix.txt";
    const char *output_file = "sparse_matrix.txt";

    scan_matrix(input_file, matrix, &rows, &cols);
    write_sparse(output_file, matrix, rows, cols);

    printf("Sparse matrix written to %s\n", output_file);
    return 0;
}
