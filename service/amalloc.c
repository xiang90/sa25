#include <stdio.h>
#include <stdlib.h>
#include "amalloc.h"

void *aMalloc_(size_t size, const char *file, int line, const char *func)
{
  void *ret;

  ret = malloc(size);
  if(ret == NULL){
    fprintf(stderr,"%s:%d: in function %s: malloc error out of memory!\n", file, line, func);
    exit(1);
  }
  return ret;
}

void *aCalloc_(size_t num, size_t size, const char *file, int line, const char *func)
{
  void *ret;

  ret = calloc(num, size);
  if(ret == NULL){
    fprintf(stderr,"%s:%d: in function %s: calloc error out of memory!\n", file, line, func);
    exit(1);
  }
  return ret;
}

void *aRealloc_(void *p, size_t size, const char *file, int line, const char *func)
{
  void *ret;

  ret = realloc(p, size);
  if(ret == NULL){
    fprintf(stderr,"%s:%d in function %s: realloc error out of memory!\n", file, line, func);
    exit(1);
  }
  return ret;
}
