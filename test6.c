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
  printf("The purpose of this test is to make sure that reallocation is working. If there is too much space, \nalso checking to see if it's creating a new empty memEntry, we are actually using that new empty memEntry here\n");

  printf("size of struct random is %ld\n", sizeof(struct random));
  struct random *ptr0 = (struct random *) malloc(sizeof(struct random)*5);

  int * ptr1 = (int *) malloc(sizeof(int)*10);

  free(ptr0);

  ptr0 = (struct random *) malloc(sizeof(struct random)*4);
  
  int * ptr2 = (int *) malloc(sizeof(int)*15);

  free(ptr2);
  free(ptr1);
  free(ptr0);

  return 0;
}
