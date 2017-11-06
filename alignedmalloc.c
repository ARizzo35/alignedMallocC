/**
 * @file alignedmalloc.c
 * -------------------
 *
 * Implementation of aligned_malloc() and aligned_free()
 *
 * Last Modified: Sat Nov  4 00:35:48 PDT 2017</pre>
 * @author Adam Rizkalla
 */

#include <stdlib.h>
#include <stdio.h>


void *aligned_malloc(size_t alignment, size_t size)
{
  void *ptr;
  void **aligned;

  if ((ptr = (void*)malloc(size + (alignment-1) + sizeof(void*))) == NULL)
    return NULL;

  aligned = (void**)((size_t)ptr + sizeof(void*));
  if (((size_t)(aligned) % alignment) > 0)
      aligned += (alignment - (((size_t)(aligned)) % alignment))/sizeof(void*);
  *(aligned-1) = ptr;

  return aligned;
}

void aligned_free(void *ptr)
{
  free(*(((void**)ptr)-1));
}

void main (int argc, char *argv[])
{
  char **endptr;
  char *p = (char*)aligned_malloc(strtol(argv[1], endptr, 10), 100);

  printf ("%s: %p\n", argv[1], p);
  aligned_free(p);
}
