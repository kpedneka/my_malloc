#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mymalloc.h"


struct something_
{

  int number;
  char character;

};

typedef struct something_ something;

something* initalize(int n, char c)
{
  something* temp = (something*)malloc(sizeof(something));
  temp->number = n;
  temp->character = c;
  return temp;

}


int main (int argc, char** argv)
{

  something* ptr = malloc(sizeof(int));
  ptr = initalize(3,'a');

  something* ptr1 = initalize(1,'c');

  free(ptr);
  free(ptr1);

  return 0;
}
