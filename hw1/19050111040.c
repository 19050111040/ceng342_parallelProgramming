/*
Furkan Rıza Parlak
19050111040
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "hellomake.h"

#define N 1040
#define M 140

int A[M][N], B[M], C[N];

int main(int argc, char *argv[])
{
  int i, j, rank, size;
  double start, end, cpu_time_used;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int elements_per_process = (N * M) / size;
  int start_index = rank * elements_per_process;
  int end_index = start_index + elements_per_process;

  if (rank == 0)
  {
    for (i = 0; i < N; i++)
    {
      for (j = 0; j < N; j++)
      {
        A[i][j] = rand() % 100;
      }
    }

    for (i = 0; i < M; i++)
    {
      B[i] = rand() % 100;
    }
  }

  // Broadcast vector B to all processes
  MPI_Bcast(B, M, MPI_INT, 0, MPI_COMM_WORLD);

  // Perform matrix-vector multiplication in parallel
  start = MPI_Wtime();
  matrixMultiplication(start_index, end_index, int N, int **A, int *B, int *C)
      end = MPI_Wtime();

  // Print the time taken for the computation
  cpu_time_used = end - start;
  printf("Process %d took %f seconds\n", rank, cpu_time_used);

  // Gather the results from all processes and verify the result on process 0
  MPI_Gather(&C[start_index], elements_per_process, MPI_INT, C, elements_per_process, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank == 0)
  {
    // Verify the result by comparing it with the sequential computation
    int *C_seq = (int *)malloc(N * sizeof(int));
    for (i = 0; i < N; i++)
    {
      C_seq[i] = 0;
      for (j = 0; j < M; j++)
      {
        C_seq[i] += A[i][j] * B[j];
      }
    }

    int is_equal = 1;
    for (i = 0; i < N; i++)
    {
      if (C[i] != C_seq[i])
      {
        is_equal = 0;
        break;
      }
    }

    if (is_equal)
    {
      printf("Result is correct\n");
    }
    else
    {
      printf("Result is incorrect\n");
    }

    free(C_seq);
  }

  // Finalize MPI
  MPI_Finalize();
  return 0;
}
