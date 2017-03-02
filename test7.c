#include<stdio.h>
#include<stdlib.h>
#include "mymalloc.h"

int main(int argc, char **argv)
{
  printf("The purpose of this test is to see what happens when you call free on a pointer that doesn't point to the beginning of a block\n");

  int *ptr1 = (int *) malloc(sizeof(int)*2);
  ptr1[0] = 34124;
  ptr1[1] = 123124;

  printf("values are %d %d\n", ptr1[0], ptr1[1]);

  int *ptr2 = (int *) malloc(sizeof(int));
  *ptr2 = 234235;

  int *ptr = (int *) malloc(sizeof(int)*8);
  int i;
  for (i = 0; i < 8; i++)
    {
      ptr[i] = i;
    }
  for (i = 0; i < 8; i++)
    {
      printf("values are %d\n",ptr[i]);
    }

  int *ptr3 = (int *) malloc(sizeof(int)*3);
  ptr3[1] = 0;
  
  free(ptr3+1);
  free(ptr2+2);
  free(ptr-1);
  free(ptr1-100);
  
  return 0;
}
