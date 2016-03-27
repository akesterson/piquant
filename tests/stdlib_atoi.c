#include "stdlib.h"

#define NULL 0x00

int main(void)
{
  if ( atoi("1234\0") != 1234 ) return 1;
  if ( atoi("65536\0") != 65536 ) return 2;
  if ( atoi("-32767\0") != -32767 ) return 3;
  return 0;
}
