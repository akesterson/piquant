#include "string.h"

int main(void)
{
  if ( strlen("Test") != 4 ) return 1;
  if ( strlen("Th\0ing") != 2 ) return 2;
  if ( strlen(NULL) != 0 ) return 3;
  return 0;
}
