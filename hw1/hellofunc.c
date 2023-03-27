#include "hellomake.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void matrixMultiplication(int rows, int cols, char *filename)
{ 
  printf("rows: %d, cols: %d, filename: %s\n", rows, cols, filename);
  double *matrix = (double *)calloc(rows * cols, sizeof(double));
  generate_random_matrix(rows, cols, matrix);

  double *vector = (double *)malloc(cols * sizeof(double));
  for (int i = 0; i < cols; i++)
  {
    vector[i] = ((double)rand() / (double)RAND_MAX) * 99.0 + 1.0;
  }

  double *result = (double *)malloc(rows * sizeof(double));
  for (int i = 0; i < rows; i++)
  {
    double row_sum = 0;
    for (int j = 0; j < cols; j++)
    {
      row_sum += matrix[i * cols + j] * vector[j];
    }
    result[i] = row_sum;
  }

  FILE *output_file = fopen(filename, "w");
  fprintf(output_file, "THE MATRIX\n");
  for (int i = 0; i < rows; i++)
  {
    double row_sum = 0;
    for (int j = 0; j < cols; j++)
    {
      fprintf(output_file, "%.2lf\t", matrix[i * cols + j]);
    }
    fprintf(output_file, "\n");
  }

  fprintf(output_file, "\n\nTHE VECTOR:\n");
  for (int i = 0; i < cols; i++)
  {
    fprintf(output_file, "%.2lf\n", vector[i]);
  }

  fprintf(output_file, "\n\nTHE MULTIPLICATION VECTOR:\n");
  for (int i = 0; i < rows; i++)
  {
    fprintf(output_file, "%.2lf\n", result[i]);
  }
  fclose(output_file);

  free(result);
  free(matrix);
  free(vector);
}

void generate_random_matrix(int rows, int cols, double *matrix)
{
  srand(905011104);
  for (int i = 0; i < rows * cols; i++)
  {
    matrix[i] = ((double)rand() / (double)RAND_MAX) * 99.0 + 1.0;
  }
}
