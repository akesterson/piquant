#include "string.h"

int main(void)
{
  char buffer[32];
  char *src = "Test String";
  int i = 0 ;
  if ( strncat((char *)&buffer, NULL, 0) != 0 ) return 1;
  if ( strncat(NULL, NULL, 0) != 0 ) return 2;
  if ( strncat(NULL, src, 0) != 0 ) return 3;

  if ( strncat((char *)&buffer, src, 11) == 0 ) return 4;

  for ( i = 0; i < 11 ; i++  ) {
    if ( buffer[i] != *(src + (sizeof(char) * i)) ) return i + 5; 
  }
  if ( buffer[11] != '\0' ) return 12 + 5;

  return 0;
}
