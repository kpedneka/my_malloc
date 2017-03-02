#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mymalloc.h"


int main (int argc, char** argv)
{

  int p = 5;
  int* ptr = (int*)malloc(sizeof(int));
  ptr = &p;
  //  int** ptr1 = ptr;

  free(ptr);
  // free(ptr1);

  return 0;
}
