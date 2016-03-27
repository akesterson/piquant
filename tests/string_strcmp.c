#include "string.h"

int main(void)
{
  if ( strcmp(NULL, NULL) != 1 ) return 1;
  if ( strcmp("Test", NULL) != 1 ) return 2;
  if ( strcmp(NULL, "Test") != 1 ) return 3;
  if ( strcmp("Test", "Test") != 0 ) return 4;
  if ( strcmp("test", "Test") != 1 ) return 5;
  if ( strcmp("Test1", "Test") != 1 ) return 6;

  return 0;
}
