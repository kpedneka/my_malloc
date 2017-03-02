#include<stdio.h>
#include<stdlib.h>
#include "mymalloc.h"

int main(int argc, char **argv)
{
  printf("The purpose of this test is to see if malloc allocates the proper space for arrays, we print values to make sure that it's all ok\n");
  int *ptr1 = (int *) malloc(sizeof(int)*2);
  ptr1[0] = 123;
  ptr1[1] = 456;

  printf("values of this array are %d %d\n", ptr1[0], ptr1[1]);

  int *ptr2 = (int *) malloc(sizeof(int));
  *ptr2 = 789;

  int *ptr = (int *) malloc(sizeof(int)*8);
  int i;
  for (i = 0; i < 8; i++)
    {
      ptr[i] = i;
    }
  printf("values of this array are");
  for (i = 0; i < 8; i++)
    {
      printf(" %d",ptr[i]);
    }
  printf("\n");

  int *ptr3 = (int *) malloc(sizeof(int)*3);
  ptr[0] = 101112;
  ptr[1] = 131415;
  ptr[2] = 161718;
  printf("values of this array are");
  for (i = 0; i < 3; i++)
    {
      printf(" %d",ptr[i]);
    }
  printf("\n");


  free(ptr3);
  free(ptr2);
  free(ptr);
  free(ptr1);

  return 0;
}
