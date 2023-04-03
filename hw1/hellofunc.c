#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void matrixMultiplication(int rank, int size, int N, int **A, int *B, int *C)
{
  int i, j;
  int chunk_size = N / size;
  int start = rank * chunk_size;
  int end = (rank + 1) * chunk_size;

  // Compute the local part of the result vector
  for (i = start; i < end; i++)
  {
    C[i] = 0;
    for (j = 0; j < M; j++)
    {
      C[i] += A[i][j] * B[j];
    }
  }

  // Reduce the local results to the global result
  if (rank == 0)
  {
    for (i = 1; i < size; i++)
    {
      MPI_Recv(&C[i * chunk_size], chunk_size, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
  }
  else
  {
    MPI_Send(&C[start], chunk_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }
}
