#include "types.h"
#include "stdlib.h"

char dtoa(int d)
{
  switch (d) {
  case 0: return '0'; break;
  case 1: return '1'; break;
  case 2: return '2'; break;
  case 3: return '3'; break;
  case 4: return '4'; break;
  case 5: return '5'; break;
  case 6: return '6'; break;
  case 7: return '7'; break;
  case 8: return '8'; break;
  case 9: return '9'; break;
  }
  return NULL;
}

int atoi(char *nptr)
{
  int value = 0;
  char *ptr = nptr;
  int multiplier = 1;

  if ( nptr == NULL ) {
    return 0;
  }
  while ( isdigit(*ptr) == 1 ) {
    ptr += 1;
  }
  ptr -= 1;
  while ( ptr >= nptr) {
    value += (((int)(*ptr--) - 0x30) * multiplier);
    multiplier *= 10;
  }
  return value;
}

int isdigit(int c)
{
  if (c >= 0x30 && c <= 0x39) {
    return 1;
  }
  return 0;
}

int isupper(int c)
{
  if (c >= 0x41 && c <= 0x5A) {
    return 1;
  }
  return 0;
}

int islower(int c)
{
  if (c >= 0x61 && c <= 0x7A) {
    return 1;
  }
  return 0;
}

int isalnum(int c)
{
  if ( isupper(c) || islower(c) || isdigit(c) ) {
    return 1;
  }
  return 0;    
}

int isxdigit(int c)
{
  if ( isdigit(c) || 
       (c >= 0x41 && c <= 0x46) ||
       (c >= 0x61 && c <= 0x66)
       ) {
    return 1;
  }
  return 0;
}
