#include<stdio.h>
#include<stdlib.h>
#include "mymalloc.h"

struct random
{
  char someArr[400];
  int anotherArr[20];
  struct random *next;
};

int main(int argc, char **argv)
{
  printf("The purpose of this test is to see if malloc will create a new memEntry because we are freeing \nsomething of sizeof(struct random)*5 but and then hope to allocate something of sizeof(struct random)*4 \nso there is free space in this reused block of size of the difference between the two\n");
  struct random *ptr0 = (struct random *) malloc(sizeof(struct random)*5);

  int * ptr1 = (int *) malloc(sizeof(int)*10);

  free(ptr0);

  ptr0 = (struct random *) malloc(sizeof(struct random)*4);

  free(ptr1);
  free(ptr0);

  return 0;
}
