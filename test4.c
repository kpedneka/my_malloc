#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mymalloc.h"

struct random
{
  char someArr[400];
  int anotherArr[20];
  struct random *next;
};

int main(int argc, char **argv)
{
  printf("The purpose of this test is to see if we can make linked lists with our malloc function, are all the memory addresses correct?\n");
  struct random *ptr = (struct random *) malloc(sizeof(struct random));
  strcpy(ptr->someArr, "PTR: This is just a test, if this works, then I'm pretty sure that our malloc implementation is okPTR: This is just a test, if this works, then I'm pretty sure that our malloc implementation is okPTR: This is just a test, if this works, then I'm pretty sure that our malloc implementation is okPTR: This is just a test, if this works, then I'm pretty sure that our [THAT WAS JUST A 400 BYTE STRING]");
  int i;
  for (i = 0; i < 20; i++)
    {
      ptr->anotherArr[i] = i*10;
    }

  struct random *ptr1 = (struct random *) malloc(sizeof(struct random));
  strcpy(ptr1->someArr, "PTR 1: This is just a test, if this works, then I'm pretty sure that our malloc implementation is solid af");
  for (i = 0; i < 20; i++)
    {
      ptr1->anotherArr[i] = i*10;
    }

  struct random *ptr2 = (struct random *) malloc(sizeof(struct random));
  strcpy(ptr2->someArr, "PTR 2: This is just a test, if this works, then I'm pretty sure that our malloc implementation is solid af");
  for (i = 0; i < 20; i++)
    {
      ptr2->anotherArr[i] = i*10;
    }

  struct random *ptr3 = (struct random *) malloc(sizeof(struct random));
  strcpy(ptr3->someArr, "PTR 3: This is just a test, if this works, then I'm pretty sure that our malloc implementation is solid af");
  for (i = 0; i < 20; i++)
    {
      ptr3->anotherArr[i] = i*10;
    }

  ptr->next = ptr1;
  ptr1->next = ptr2;
  ptr2->next = ptr3;
  ptr3->next = NULL;

  struct random *ptr4 = ptr;
  i = 0;
  while (ptr4 != NULL)
    {
      printf("Printing values for ptr%d\n at address %p", i, ptr4);
      printf("%s\n", ptr4->someArr);
      int j;
      for (j = 0; j < 20; j++)
	{
	  printf("%d ", ptr4->anotherArr[j]);
	}
      printf("\n\n");
      ptr4 = ptr4->next;
      i++;
    }

  printf("%ld\n",sizeof(struct random));
  free(ptr3);
  free(ptr2);
  free(ptr1);
  free(ptr);
  free(ptr4);

  return 0;
}
