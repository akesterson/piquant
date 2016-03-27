#include "stdlib.h"

#define NULL 0x00

int main(void)
{
  const char *uptest = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const char *lowtest = "abcdefghijklmnopqrstuvwcyz";
  char *ptr = NULL;

  for ( ptr = (char *)uptest; *ptr != '\0' ; ptr++ ) {
    if ( isupper((int)*ptr) != 1 ) return (int)(ptr - uptest);
  }
  for ( ptr = (char *)lowtest; *ptr != '\0' ; ptr++ ) {
    if ( isupper((int)*ptr) != 0 ) return (int)(26 + (ptr - lowtest));
  }


  for ( ptr = (char *)lowtest; *ptr != '\0' ; ptr++ ) {
    if ( islower((int)*ptr) != 1 ) return (int)(52 + (ptr - uptest));
  }
  for ( ptr = (char *)uptest; *ptr != '\0' ; ptr++ ) {
    if ( islower((int)*ptr) != 0 ) return (int)(78 + (ptr - lowtest));
  }

  return 0;
}
