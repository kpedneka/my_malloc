#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mymalloc.h"

int main (int argc, char ** argv)
{
  printf("The purpose of this test is to just see that it can allocate multiple small blocks of data. Pay attention to addresses\n");
  //printf("the size of a memEntry is %ld\n\n", (sizeof(struct memEntry)));
  char * ptr = (char *) malloc(sizeof(char)*8);
  strcpy(ptr, "hello");
  printf("%s\n",ptr);

  int * ptr1 = (int *) malloc(sizeof(int));
  *ptr1 = 17;
  printf("%d\n", *ptr1);

  char *ptr2 = (char *)malloc(sizeof(char)*24);
  strcpy(ptr2, "hey this is 24 chars  ");
  printf("%s\n",ptr2);

  char *ptr3 = (char *)malloc(sizeof(char)*14);
  strcpy(ptr3, "I'm bored");
  printf("%s\n",ptr3);

  free(ptr3);
  free(ptr1);
  free(ptr);
  free(ptr2);

  return 0;
}
