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
  printf("The purpose of this test is to see if we can make linked lists with our malloc function, are all the memory addresses correct?\n This allocates all data from the right till it fills up the whole capacity of the memblock");
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

  struct random *ptr4 = (struct random *) malloc(sizeof(struct random));
  strcpy(ptr4->someArr, "PTR 4: This is just a test, if this works, then I'm pretty sure that our malloc implementation is solid af");
  for (i = 0; i < 20; i++)
    {
      ptr4->anotherArr[i] = i*10;
    }

  struct random *ptr5 = (struct random *) malloc(sizeof(struct random));
  strcpy(ptr5->someArr, "PTR 5: This is just a test, if this works, then I'm pretty sure that our malloc implementation is solid af");
  for (i = 0; i < 20; i++)
    {
      ptr5->anotherArr[i] = i*10;
    }

  struct random *ptr6 = (struct random *) malloc(sizeof(struct random));
  strcpy(ptr6->someArr, "PTR 6: This is just a test, if this works, then I'm pretty sure that our malloc implementation is solid af");
  for (i = 0; i < 20; i++)
    {
      ptr6->anotherArr[i] = i*10;
    }

  struct random *ptr7 = (struct random *) malloc(sizeof(struct random));
  strcpy(ptr7->someArr, "PTR 7: This is just a test, if this works, then I'm pretty sure that our malloc implementation is solid af");
  for (i = 0; i < 20; i++)
    {
      ptr7->anotherArr[i] = i*10;
    }
  
  struct random *ptr8 = (struct random *) malloc(sizeof(struct random));
  strcpy(ptr8->someArr, "PTR 8: This is just a test, if this works, then I'm pretty sure that our malloc implementation is solid af");
  for (i = 0; i < 20; i++)
    {
      ptr8->anotherArr[i] = i*10;
    }
 
  struct random *ptr9 = (struct random *) malloc(sizeof(struct random));

  ptr->next = ptr1;
  ptr1->next = ptr2;
  ptr2->next = ptr3;
  ptr3->next = ptr4;
  ptr4->next = ptr5;
  ptr5->next = ptr6;
  ptr6->next = ptr7;
  ptr7->next = ptr8;
  ptr8->next = ptr9;

  struct random *ptr10 = ptr;
  i = 0;
  while (ptr10 != NULL)
    {
      printf("Printing values for ptr%d\n at address %p", i, ptr10);
      printf("%s\n", ptr10->someArr);
      int j;
      for (j = 0; j < 20; j++)
	{
	  printf("%d ", ptr10->anotherArr[j]);
	}
      printf("\n\n");
      ptr10 = ptr10->next;
      i++;
    }

  printf("%ld\n",sizeof(struct random));

  free(ptr9);
  free(ptr8);
  free(ptr7);
  free(ptr6);
  free(ptr5);
  free(ptr4);
  free(ptr3);
  free(ptr2);
  free(ptr1);
  free(ptr);
  free(ptr10);
  return 0;
}
