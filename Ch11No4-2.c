#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 100
#define MAX_COLS 100

void scan_sparse(const char *filename, int matrix[MAX_ROWS][MAX_COLS], int *rows, int *cols) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open input file");
        return;
    }

    int non_zero_count;
    fscanf(file, "%d %d", rows, cols); 
    fscanf(file, "%d", &non_zero_count);

    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < non_zero_count; i++) {
        int row, col, value;
        fscanf(file, "%d %d %d", &row, &col, &value);
        matrix[row][col] = value;
    }

    fclose(file);
}

void write_matrix(const char *filename, int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open output file");
        return;
    }

    fprintf(file, "%d %d\n", rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
    int matrix[MAX_ROWS][MAX_COLS];
    int rows, cols;

    const char *input_file = "sparse_matrix.txt";
    const char *output_file = "traditional_matrix.txt";

    scan_sparse(input_file, matrix, &rows, &cols);
    write_matrix(output_file, matrix, rows, cols);

    printf("Traditional matrix written to %s\n", output_file);
    return 0;
}
