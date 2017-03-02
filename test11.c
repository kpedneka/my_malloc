#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mymalloc.h"
struct something_
{
  int id;
  float value;
  struct something_* next;
};

typedef struct something_ something;


something* intialize (int i, float v)
{
  something* temp = (something*)malloc(sizeof(temp));
  temp->id = i;
  temp->value = v;
  temp->next = NULL;
  return temp;

}

int main(int argc, char** argv)
{
  something* head = intialize(1, 1.23);
  //  int count = 0;
  //something* ptr = head;

  something* ptr1 = intialize(2, 1.34);
  something* ptr2 = intialize(3, 4.34);
  something* ptr3 = intialize(4, 4.234);

  head->next = ptr1;
  ptr1->next = ptr2;
  ptr2->next = ptr3;

  /*for(count = 0; count<10; count++)
    {
      while(ptr!=NULL)
	{
	  ptr = ptr->next;
	}
      
      something* temp = intialize(count, 2.34);
      ptr->next = temp;

    }
  */

  //head = ptr;

  free(head);
  free(ptr1);
  free(ptr2);
  free(ptr3);
  return 0;
}
