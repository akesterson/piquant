#include "string.h"

int main(void)
{
  char testblock[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  char testblock2[6] = {50, 60, 70, 80, 90, 100};
  int i = 0;

  memcpy((void *)&testblock, (void *)&testblock2, (sizeof(char)*6));
  for ( i = 0; i < 6; i++) {
    if ( testblock[i] != testblock2[i] ) return (i + 1);
  }
  if ( testblock[6] != 7 ) return 7;
  if ( testblock[7] != 8 ) return 8;
  return 0;
}
