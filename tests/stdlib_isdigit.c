#include "stdlib.h"

#define NULL 0x00

int main(void)
{
  if ( isdigit((int)'0') != 1 ) return 1;
  if ( isdigit((int)'1') != 1 ) return 2;
  if ( isdigit((int)'2') != 1 ) return 3;
  if ( isdigit((int)'3') != 1 ) return 4;
  if ( isdigit((int)'4') != 1 ) return 5;
  if ( isdigit((int)'5') != 1 ) return 6;
  if ( isdigit((int)'6') != 1 ) return 7;
  if ( isdigit((int)'7') != 1 ) return 8;
  if ( isdigit((int)'8') != 1 ) return 9;
  if ( isdigit((int)'9') != 1 ) return 10;
  if ( isdigit((int)'a') != 0 ) return 11;
  return 0;
}
