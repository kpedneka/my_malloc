#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mymalloc.h"


int main (int argc, char** argv)
{

  int * ptr = (int *) calloc(4, sizeof(int));
  ptr[0] = 0;
  ptr[1] = 1;
  ptr[2] = 2;
  ptr[3] = 3;

  int i;
  printf("values of ptr are ");
  for (i = 0; i < 4; i++)
    {
      printf(" %d", ptr[i]);
    }
  printf("\n");
  free(ptr);

  return 0;
}
