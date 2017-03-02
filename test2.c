#include<stdio.h>
#include<stdlib.h>

#include "mymalloc.h"

int main(int argc, char ** argv)
{
  printf("The purpose of this test is to check if free handles double free or freeing something that was not malloced\n");
  //printf("the size of a memEntry is %ld\n\n", sizeof(struct memEntry));
  char * ptr = (char *)malloc(sizeof(char)*25);
  
  int * ptr1 = (int *)malloc(sizeof(int));

  char * ptr2 = (char *)malloc(5001);
  free(ptr2);
  free(ptr1);
  free(ptr);

  int * ptr3 = (int *)malloc(sizeof(int));
  *ptr3 = 6;
  free(ptr3);
  free(ptr3);

  char array[23] = "hello there";
  free(array);

  return 0;
}
