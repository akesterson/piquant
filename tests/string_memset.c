#include "string.h"

int main(void)
{
  char testblock[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  int i = 0;

  memset((void *)&testblock, 0x00, (sizeof(char) * 8));
  for ( i = 0; i < 8; i++) {
    if ( testblock[i] != 0x00 ) return (i + 1);
  }
  if ( testblock[8] != 9 ) return 8;
  if ( testblock[9] != 10 ) return 9;
  if ( testblock[10] != 11 ) return 10;
  if ( testblock[11] != 12 ) return 11;
  return 0;
}
