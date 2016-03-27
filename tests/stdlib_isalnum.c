#include "stdlib.h"

#define NULL 0x00

int main(void)
{
  const char *postest = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
  const char *negtest = "~!@#$%^&*()_+{}|[]\\:\";'<>?,./`/*-.";
  char *ptr = NULL;

  for ( ptr = (char *)postest; *ptr != '\0' ; ptr++ ) {
    if ( isalnum((int)*ptr) != 1 ) return (int)(ptr - postest);
  }
  for ( ptr = (char *)negtest; *ptr != '\0' ; ptr++ ) {
    if ( islower((int)*ptr) != 0 ) return (int)(100 + (ptr - negtest));
  }

  return 0;
}
