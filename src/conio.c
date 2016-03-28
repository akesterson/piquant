#include "types.h"
#include "conio.h"
#include "screen.h"

void _putch(char c)
{
  __asm__(
	  "push bx;"
	  "push ax;"
	  "mov bx, sp;"
	  "mov al, %0;"
	  "mov ah, 0x0e;"
	  "mov bh, 0x00;"
	  "mov bl, 0x07;"
	  "int 0x10;"
	  "pop ax;"
	  "pop bx;"
	  : : "r" (c)
	  );
    return;
}

void _cputs(char *ptr) 
{
  if ( ptr == NULL ) {
    return;
  }
  while ((char)*ptr != 0x0) { 
    _putch((char)*ptr);
    if (*ptr == '\n') {
      _cursor_y += 1;
      _cursor_x = 0;
      setCursorPosition(_cursor_x, _cursor_y);
    } else {
      advanceCursor();
    }
    ptr += 1;
  }
  return;
}

char _getkey(char *dest)
{
  char echo;
  char scancode;
/* #asm */
/*   push ax; */
/*   mov ah, #0x10; */
/*   int 0x16; */
/*   mov [bp-6], ah; */
/*   mov [bp-5], al; */
/*   pop ax; */
/* #endasm */
  *dest = echo;
  return scancode;
}

char *_cgets(char *d)
{
  char *orig = d;
  char scancode;
  char printable;

  if ( d == NULL ) {
    return NULL;
  }

  scancode = _getkey(&printable);

  while ( scancode != NULL ) {
    if ( scancode == 0x0e ) {
      if ( d > orig ) {
	backupCursor();
	setCursorPosition(_cursor_x, _cursor_y);
	d -= 1;
	_putch(0x0);
      }
    } else if ( scancode == 0x1c ) {
      break;
    } else {
      *(d++) = printable;
      _putch(printable);
      advanceCursor();
    } 
    scancode = _getkey(&printable);
  }
  
 __cgets_finish_loop:
  *d = NULL;
  return orig;
}
