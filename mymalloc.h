#ifndef mymalloc_h

//assume this is the metadata struct (size ~ 20 bytes) 
struct memEntry
{
  unsigned int size;
  int isFree;
  void *data;
  struct memEntry *prev;
  struct memEntry *next;
};

#define malloc(x) mymalloc((x), __FILE__, __LINE__)
#define calloc(x, y) mycalloc((x),(y), __FILE__, __LINE__)
#define free(x) myfree((x), __FILE__, __LINE__)

void* mycalloc(unsigned int nitems, unsigned int sizenitems, char* file, unsigned int line);
void * mymalloc (unsigned int size, char * file, unsigned int line);
void myfree(void * data, char * file, unsigned int line);
void tooMuchSpace(struct memEntry * ptr, unsigned int size, char * memblock);
void mergeBlocks(struct memEntry * ptr);
struct memEntry * findMemSmall(unsigned int size, struct memEntry * head);
struct memEntry * addFromLeft(char * memblock, unsigned int size);
struct memEntry * addFromRight(char * memblock, unsigned int size);
struct memEntry * initialize(char * memblock, unsigned int size);
struct memEntry * findAnyMem(char* memblock, unsigned int size);

#endif
