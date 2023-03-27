#include "hellomake.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
  // call a function in another file
  int num1 = atoi(argv[1]);
  int num2 = atoi(argv[2]);
  matrixMultiplication(num1, num2, argv[3]);
  return (0);
}
