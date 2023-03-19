#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hellomake.h"

int i = 0;
int j = 0;

int main(int argc, char *argv[]) {
     if (argc != 4) {
         printf("%s <rows> <cols> <output_filename>\n", argv[0]);
         return 1;
     }
     int rows = atoi(argv[1]);
     int cols = atoi(argv[2]);
     char *output_filename = argv[3];

     srand(time(NULL));

     // Allocate
     double **matrix = (double **)malloc(rows * sizeof(double *));
     for (i = 0; i < rows; i++) {
         matrix[i] = (double *)calloc(cols, sizeof(double));
         for (j = 0; j < cols; j++) {

             matrix[i][j] = ((double)rand() / RAND_MAX) * 99.0 + 1.0;
         }
     }

     // Allocate 2
     double *vector = (double *)calloc(cols, sizeof(double));
     for (i = 0; i < cols; i++) {
     // Random number
         vector[i] = ((double)rand() / RAND_MAX) * 99.0 + 1.0;
     }

     // Matrix multiplication
     double *result = (double *)calloc(rows, sizeof(double));
     for (i = 0; i < rows; i++) {
         for (j = 0; j < cols; j++) {
             result[i] += matrix[i][j] * vector[j];
             }
     }

     // Write to file
     FILE *output_file = fopen(output_filename, "w");
     for (i = 0; i < rows; i++) {
         fprintf(output_file, "%.2f\n", result[i]);
     }
     fclose(output_file);

     // Clear memory
     for (i = 0; i < rows; i++) {
         free(matrix[i]);
     }
     free(matrix);
     free(vector);
     free(result);

     return 0;
 }
