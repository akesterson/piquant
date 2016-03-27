#include "stdlib.h"

#define NULL 0x00

int main(void)
{
  if ( dtoa(0) != '0' ) return 1;
  if ( dtoa(1) != '1' ) return 2;
  if ( dtoa(2) != '2' ) return 3;
  if ( dtoa(3) != '3' ) return 4;
  if ( dtoa(4) != '4' ) return 5;
  if ( dtoa(5) != '5' ) return 6;
  if ( dtoa(6) != '6' ) return 7;
  if ( dtoa(7) != '7' ) return 8;
  if ( dtoa(8) != '8' ) return 9;
  if ( dtoa(9) != '9' ) return 10;
  if ( dtoa(11) != NULL ) return 11;
  if ( dtoa(-1) != NULL ) return 12;
  return 0;
}
