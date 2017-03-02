#include<stdio.h>
#include<stdlib.h>
#include "mymalloc.h"
#include <string.h>
enum boolean
  {
    true,
    false
  };

//this is the space from where we will allocate data
static char memblock[5000];

//this is the global head pointer for all memEntries
struct memEntry *head;

//iterates through memEntries which have user space <= 30 bytes to find a free memEntry
//returns struct memEntry on success, NULL on failure
struct memEntry * findMemSmall(unsigned int size, struct memEntry * head)
{
  struct memEntry * ptr = head;
  if (ptr == NULL)
    return NULL;

  while (ptr != NULL)
    {
      if (ptr->size > 30)
	return ptr->prev; //this will either be NULL or the last node which has size <= 30
      if (ptr->isFree == true && ptr->size >= size)
	return ptr;
      if (ptr->next == NULL)
	return ptr;
      ptr = ptr->next;
    }

  return ptr; //went to the end of the list, last node has size <= 30
}


//traverses linked list of memEntries to add from left
//basically we are traversing from left and then inserting after a node
struct memEntry * addFromLeft(char * memblock, unsigned int size)
{
  struct memEntry * ptr = NULL;

  //need to traverse memEntries first to see if any current nodes of size <= 30 can hold it
  ptr = findMemSmall(size, head); //this value can be NULL
  //printf("findMemSmall returned address of %p \n", ptr);

  //if it returned a non-null value, we either found a memEntry struct that is free or the last memEntry that has user size <= 30
  if (ptr != NULL)
    {
      //this be the last memEntry struct with user size <= 30
      if (ptr->isFree == false)
	{
	  char * endUserblock = (char *) ptr+sizeof(struct memEntry)+(ptr->size);
	  struct memEntry * temp = NULL;
	  char * placeholder;
	 
	  //check addresses to see if we have enough space for memEntry + user space
	  //if there are no more nodes, look at end of array
	  if (ptr->next == NULL)
	    {
	      char * endMemblock = memblock+5000;	     
	      if ((endMemblock - endUserblock) > (sizeof(struct memEntry)+size))
		{
		  placeholder = (char *) ptr+sizeof(struct memEntry)+(ptr->size)+1;
		  temp = (struct memEntry *) placeholder;
		  endUserblock = (char *) temp+sizeof(struct memEntry)+(ptr->size);
		  //printf("there are  %ld bytes left\n", (endMemblock-endUserblock));
		  temp->prev = ptr;
		  temp->next = ptr->next;
		  ptr->next = temp;
		  return temp;
		}
	      else
		{
		  //printf("there was not enough space\n");
		  return NULL;
		}
	    }
	  else //there are more nodes, so compare to them
	    {
	      struct memEntry * next = ptr->next;
	      char * startNextUserblock = (char *) next;
	      if ((startNextUserblock - endUserblock) > (sizeof(struct memEntry)+size))
		{
		  //printf("there is %ld space\n", (startNextUserblock-endUserblock));
		  temp = ptr+sizeof(struct memEntry)+(ptr->size)+1;
		  temp->prev = ptr;
		  temp->next = ptr->next;
		  ptr->next = temp;
		  return temp;
		}
	      else
		{
		  //printf("there was not enough space\n");
		  return NULL;
		}
	    }
	  return NULL;
	}
      else //ptr->isFree == true !! don't worry about size, findMemSmall considered that!!
	{
	  return ptr;
	}
    }
  //else ptr is NULL only if all nodes have user space > 30 bytes or no nodes exist. Add to front
  else
    {
      ptr = (struct memEntry *) memblock;
      if (head == NULL)
	{
	  /*
	  char * endb = memblock+5000;
	  char * ends = (char *)ptr+sizeof(struct memEntry)+(size);
	  printf("there are %ld bytes left\n", (endb-ends));
	  */
	  head = ptr;
	  head->next = NULL;
	  head->prev = NULL;
	}
      else
	{
	  ptr->next = head;
	  ptr->prev = NULL;
	  head = ptr;
	}
      return head;
    }

  return NULL; //returns NULL if no space/unsuccessful search for space
}

//goes to the end of the list, then goes backwards and gives either the first
//free block which can hold the size or the first non-free block which has size > 30 to add before
//can return null if there are no nodes or no nodes with size > 30
struct memEntry* findLargest(unsigned int size, char* memblock)
{
  //printf("RIGHT: \n");
    struct memEntry* ptr = head;

    if (head == NULL)
      return NULL;

    //go to end
    while(ptr->next!=NULL)
    {
      ptr = ptr->next;
    }
    //go backwards till you find a suitable free block or the first block which has size > 30
    while (ptr->prev != NULL)
      {
	if (ptr->isFree == true && ptr->size >= size)
	  return ptr; //found a suitable free block
	if (ptr->size <= 30)
	  {
	    return ptr->next; //found a block with size <= 30
	  }
	ptr = ptr->prev;
      }
    //this would be first memEntry
    return ptr;
}

struct memEntry * addFromRight(char * memblock, unsigned int size)
{
  struct memEntry* ptr = NULL;
  ptr = findLargest(size, memblock);//this value can be null
  //printf("findLargest returned address %p\n\n", ptr);
  //  //if ptr is Not null then there are other chunks >30
  if(ptr!=NULL)
    {
      //  printf("is there a problem: ptr is not NULL\n");
      //findLargest returned us the first memEntry which has size > 30 and is not free
      if(ptr->isFree == false)
        {
	  //  printf("adding from Right: this is not free\n");
          
	  char* startUserblock = (char*)ptr;
	  struct memEntry* temp = NULL;
	  // all nodes so far added have had size > 30 (all have been addFromRight) we make a new head
	  if(ptr->prev == NULL)
            {
	      char* startMemblock = memblock;
	      //if there is enough space between start of memblock and the first memEntry (head) to add new data
	      if((startUserblock-startMemblock)>(sizeof(struct memEntry)+size))
                {
		  //printf("there is %ld space\n",(startUserblock-startMemblock));
		  temp= (struct memEntry *) ((char *) ptr-sizeof(struct memEntry)-(size)-1);
		  temp->next = ptr;
		  temp->prev = NULL;
		  ptr->prev = temp;
		  head = temp;
		  return temp;
                }
	      else //not enough space to put new data here, initialize will try again from findAnyMem
                {
		  //	  printf("there was not enough space here, findAnyMem will try again\n");
		  return NULL;
                }
            }
	  //there is something before this, has size <= 30 before
            else
	      {
                struct memEntry * prev = ptr->prev;
                char* endPrevUserblock = (char*)prev+sizeof(struct memEntry)+(prev->size);
		//if there is enough space between the end of the previous block (last block with size <= 30 bytes) and the beginning of the
		//first block with size > 30 bytes, we can add a new thing here
                if((endPrevUserblock-startUserblock)>(sizeof(struct memEntry)+size))
		  {
                    //printf("there is %ld space\n",(startUserblock-endPrevUserblock));
                    temp = ptr-sizeof(struct memEntry)-(size)-1;
                    temp->next = ptr;
                    temp->prev = ptr->prev;
                    return temp;
		  }
                else //not enough space to put new data here, initialize will try again from findAnyMem
		  {
		    // printf("there was not enough space, findAnyMem will try again\n");
                    return NULL;
		  }
	      }
	  return NULL;
        }
      else //ptr->isFree = true
	{
	  //  printf("Found a suitable free block, calling tooMuchSpace\n");
	  //this function checks to see if there is enough space to create
	  //a new memEntry struct after reallocating a recently freed block (reducing fragmentation)
	  tooMuchSpace(ptr, size, memblock);
	  return ptr;
	}
    }
  else // ptr points first allocation has size > 30 NOT NULL
    {
      //  printf("Ptr is NULL: no nodes bigger than 30, or add to very last\n");
      
      struct memEntry * temp = head;
      
      if(temp != NULL)
	{
	  //find last node with size <= 30 bytes
	  while (temp->next != NULL)
	    {
	      if (temp->next->size > 30)
		{
		  temp = temp->prev;
		  break;
		}
	      temp = temp->next;
	      }
	}
      char * endMemblock = memblock+5000;
      //ptr holds a pointer to where we want to insert a memEntry and give back a pointer to user
      struct memEntry* ptr = (struct memEntry*) (endMemblock-size-sizeof(struct memEntry)-1);
      
      //if the address of ptr is greater than the address of the beginning of memblock
      if ((char *)ptr > memblock)
	{
	  if (temp == NULL)
	    {
	      //printf("there are %ld bytes left\n", ((char *)ptr-memblock));
	      ptr->prev = NULL;
	      ptr->next = NULL;
	      head = ptr;
	      return ptr;
	    }
	  else //temp != NULL, there is a node with size <= 30 bytes
	    {
	      //printf("there are %ld bytes left\n", ((char *)ptr-memblock));
	      ptr->next = temp->next;
	      temp->next = ptr;
	      ptr->prev = temp;
	      return ptr;
	    }
	}
      else //size of what they're asking is too big
	{
	  return NULL;
	}
    }
  return NULL; //returns NULL if no space/unsuccessful search for space
}

//this function checks to see if there is enough space after a block of memory
//to add another memEntry such that a user can put some data (at least 1 byte of data)
//there too, trying to reduce fragmentation
void tooMuchSpace(struct memEntry * ptr, unsigned int size, char * memblock)
{
  //if user puts some data of some (size), temp points to where that block would end
  char *temp = (char *) ptr+sizeof(struct memEntry)+size+1;

  //this is the potential new memEntry that we will add if successful
  struct memEntry * newEntry = (struct memEntry *) temp;

  //if ptr->next == NULL, compare to end of array
  if (ptr->next == NULL)
    {
      char * endBlock = memblock+5000;
      //if there is enough space between end of memblock and where this
      //new block will end to hold a memEntry and at least 1 byte for user
      if (endBlock-temp > sizeof(struct memEntry)+1)
	{
	  newEntry->prev = ptr;
	  newEntry->next = NULL;
	  ptr->next = newEntry;
	  newEntry->size = (endBlock-((char *)newEntry+sizeof(struct memEntry)));
	  newEntry->isFree = true;
	}
    }
  //if ptr->next != NULL, compare to beginning of next memEntry
  else
    {      
      char * startNextBlock = (char *)ptr->next;
      //if there is enough space between beginning of next memEntry and 
      //end of new block to hold at least 1 byte for user
      if (startNextBlock-temp > sizeof(struct memEntry)+1)
	{
	  newEntry->prev = ptr;
	  newEntry->next = ptr->next;
	  ptr->next = newEntry;
	  newEntry->size = (startNextBlock-(char *)newEntry+sizeof(struct memEntry));
	  newEntry->isFree = true;
	}
    }
  printf("Too much space. Created a new block at address %p with size %d\n\n", newEntry, newEntry->size);
}


//Sanjana pls fill this up. DON'T FORGET TO ADD THIS TO MYMALLOC.H :-)
struct memEntry * findAnyMem(char* memblock, unsigned int size)
{
  struct memEntry* ptr = head;
  // struct memEntry* temp = NULL;
  while(ptr!=NULL)
    {

      if(ptr->isFree == true &&ptr->size>=size)
	{
	  
	  //add it here
	  ptr->size = size;
	  tooMuchSpace(ptr,size,memblock);
	  return ptr;
	}

      ptr = ptr->next;
    }
  return NULL; //if no space was found

}

//if there is no memEntry at the beginning of the array,
//creat one here
struct memEntry * initialize(char * memblock, unsigned int size)
{
  struct memEntry * ptr = NULL;

  //add from left
  if (size <= 30)
    {
      ptr = addFromLeft(memblock, size);
    }
  else   //if requested size > 30, add from right
    {
      ptr = addFromRight(memblock, size);
    }
  //all blocks <= 30 bytes or all blocks > 30 bytes were full
  //check the other ones for free blocks!
  if (ptr == NULL)
    {
      ptr = findAnyMem(memblock, size);
    }

  if (ptr != NULL) //prev, next pointers are taken care of already
    {
      ptr->size = size;
      ptr->isFree = false;
      char * dataptr = (char *)ptr+sizeof(struct memEntry)+1;
      ptr->data = (void *) dataptr;
      printf("malloced new pointer at address %p with size %d\n\n", ptr, size);
    }
  else //there really wasn't any space, checked the whole array!
    {
      return NULL;
    }

  return ptr;
}


void* mycalloc(unsigned int nitems, unsigned int sizenitems, char* file, unsigned int line)
{
  //printf("\n\naddress of head: %p \n\n", head);
  if (nitems == 0)
    {
      fprintf(stderr, "User requested 0 items of size %d bytes from line %d in file %s\n\n", sizenitems, line, file);
      return NULL;
    }
  if (sizenitems == 0)
    {
      fprintf(stderr, "User requested %d items of size 0 bytes from line %d in file %s\n\n", nitems, line, file);
      return NULL;
    }
  if ((nitems*sizenitems)+sizeof(struct memEntry) >= 5000)
    {
      fprintf(stderr, "User requested size %d*%d bytes exceeds max capacity of 5000 bytes from line %d in file %s\n\n", sizenitems, nitems, line, file);
      return NULL;
    }
  struct memEntry * ptr = NULL;

  //call to create a memEntry, can be NULL
  ptr = initialize(memblock, (nitems*sizenitems));

  //if unable to allocate space
  if (ptr == NULL)
    {
      fprintf(stderr, "Unable to allocate %d*%d bytes for malloc call at line %d in file %s\n\n", sizenitems, nitems, line, file);
      return NULL;
    }

  memset(ptr->data,0,ptr->size);
  return ptr->data;

}

//main malloc function, called to allocate space
void * mymalloc(unsigned int size, char *file, unsigned int line)
{
  //printf("\n\naddress of head: %p \n\n", head);
  if (size == 0)
    {
      fprintf(stderr, "User requested 0 bytes from line %d in file %s\n\n", line, file);
      return NULL;
    }
  if (size+sizeof(struct memEntry) >= 5000)
    {
      fprintf(stderr, "User requested size %d bytes exceeds max capacity of 5000 bytes from line %d in file %s\n\n", size, line, file);
      return NULL;
    }
  struct memEntry * ptr = NULL;

  //call to create a memEntry, can be NULL
  ptr = initialize(memblock, size);
  //if unable to allocate space
  if (ptr == NULL)
    {
      fprintf(stderr, "Unable to allocate %d bytes for malloc call at line %d in file %s\n\n", size, line, file);
      return NULL;
    }

  return ptr->data;

}


//mergeBlocks merges consecutive empty blocks, gets rid of the right most free block if size <= 30 bytes
//gets rid of the left most free block if size > 30 bytes
//this tries to ensure that we are always keeping space in the middle of the array
void mergeBlocks(struct memEntry * ptr)
{

  if (ptr->next != NULL && ptr->next->isFree == true) //if the next node is also empty
    {
      ptr->next = ptr->next->next; // ptr->next could now be null
    }
  if (ptr != head) //if it is not the first node, prev will not be null
    {
      ptr = ptr->prev;
      ptr->next = ptr->next->next; //ptr->next could now be null
    }
}



//free function, goes and frees stuff
//check to see if this was allocated in the range of our static char array
//check to see if it data points to beginning of allocated space (data - sizeof(struct memEntry)) should not give errors
//check is already freed in the past (prevent double freeing
void myfree (void * data, char *file, unsigned int line)
{
  struct memEntry * ptr = head;
  struct memEntry * checker = NULL;

  //check to see if data is NULL
  if (data == NULL)
    {
      fprintf(stderr, "User tried to free a NULL pointer at line %d in file %s\n\n", line, file);
      return;
    }

  //this should mean that the pointer now points to the beginning of the memEntry
  checker = (struct memEntry *) ((char *) data - sizeof(struct memEntry)-1);

  //checking to see if pointer to free is in range of memblock, to see if it'll be a valid free
  //printf("address of data: %p, address range of memblock: %p %p\n", checker, memblock, memblock+5000);
  if(((char *)checker < memblock) || ((char *)checker > memblock+5000))
    {
      fprintf(stderr, "User tried to free pointer that was not allocated by mymalloc at line %d in file %s\n\n", line, file);
      return;
    }

  //traverse memEntryies to see if we get a match
  while (ptr != NULL)
    {
      if(checker->data == data && ptr->size == checker->size)
	{
	  //printf("compared %d %p to %d %p\n", checker->size, checker, ptr->size, ptr);
	  if (checker->isFree == true)
	    {
	      fprintf(stderr, "User tried an illegal free at line %d in file %s\n\n", line, file);
	      return;
	    }
	  checker->isFree = true;	 
	  printf("we have successfully freed memEntry at %p\n\n", checker);
	  //call function for merging consecutive free blocks here
	  mergeBlocks(checker);
	  return;
	}
      //printf("%p %p\n", checker, ptr);
      ptr = ptr->next;
    }

  //if no matches, and all other checks passed, pointer must not be to beginning of of user allocated block
  fprintf(stderr, "Unable to free block, pointer did not point to beginning of block at line %d in file %s\n\n", line, file);
  return;
}

