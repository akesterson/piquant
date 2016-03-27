#include "stdlib.h"

#define NULL 0x00

int main(void)
{
  const char *postest = "ABCDEFabcdef0123456789";
  const char *negtest = "GHIJKLMNOPQRSTUVWXYZghijklmnopqrstuvwxyz~!@#$%^&*()_+{}|[]\\:\";'<>?,./`/*-.";
  char *ptr = NULL;

  for ( ptr = (char *)postest; *ptr != '\0' ; ptr++ ) {
    if ( isxdigit((int)*ptr) != 1 ) return (int)(ptr - postest);
  }
  for ( ptr = (char *)negtest; *ptr != '\0' ; ptr++ ) {
    if ( isxdigit((int)*ptr) != 0 ) return (int)(100 + (ptr - negtest));
  }

  return 0;
}
