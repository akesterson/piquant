#ifndef _STRING_H_
#define _STRING_H_

#include "types.h"

size_t strlen(char *ptr);
int strncat(char *dest, char *src, size_t n);
void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, void *src, size_t n);
int strcmp(const char *s1, const char *s2);

#endif /* _STRING_H_ */
