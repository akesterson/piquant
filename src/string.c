#include "types.h"
#include "string.h"

size_t strlen(char *ptr)
{
  char *ptr2 = ptr;
  if ( ptr == NULL ) {
    return 0;
  }

  while (*ptr2 != 0x0 ) {
    ptr2 += 1;
  }

  return ptr2 - ptr;
}

void *memset(void *s, int c, size_t n)
{
  int *d = (int *)s;
  if ( s == NULL ) {
    return NULL;
  }
  while ( (d - (int *)s) <= n ) {
    *d = c;
    d += sizeof(int);
  }
  return s;
}

void *memcpy(void *dest, void *src, size_t n)
{
  int i = 0;
  char *d = dest;
  char *s = src;

  if ( d == NULL || s == NULL ) {
    return NULL;
  }
  for ( i = 0 ; i < n ; i++ ) {
    *d++ = *s++;
  }
  *d = '\0';
  return dest;
}

int strncat(char *dest, char *src, size_t n)
{
  int c = 0;
  if ( dest == NULL || src == NULL ) {
    return 0;
  }
  dest = (dest + strlen(dest));
  while ( c++ < n ) {
    *dest++ = *src++;
  }
  return c;
}

int strcmp(char *s1, char *s2)
{
  int s1len = 0;

  if ( s1 == NULL || s2 == NULL ) {
    return 1;
  }

  s1len = strlen(s1);
  if ( s1len != strlen(s2) ) {
    return 1;
  }

  while ( *s1 != '\0' ) {
    if ( *s1 != *s2 ) {
      return 1;
    }
    s1 += sizeof(char);
    s2 += sizeof(char);
  }

  return 0;
}
