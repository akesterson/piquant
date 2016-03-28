#include "types.h"
#include "screen.h"
#include "conio.h"

char _cursor_x = 0;
char _cursor_y = 0;

void blankScreen(void)
{
  char i = 0;
  char j = 0;
  for ( i = 0 ; i < 26 ; i++ ) {
    for ( j = 0; j < 81 ; j++ ) {
      setCursorPosition(j, i);
      _putch(0x0);
    }
  }
}

void setCursorPosition(char x, char y)
{
  __asm__ (
	   "push bx;"
	   "mov sp, bx;"
	   "mov dl, %0;"
	   "mov dh, %1;"
	  : : "r" (x), "r" (y) );
  __asm__(
	  "pop bx;"
	  "push ax;"
	  "push bx;"
	  "mov ah, 0x02;"
	  "mov bx, 0x0;"
	  "int 0x10;"
	  "pop bx;"
	  "pop ax;" : : );
  return;
}

void backupCursor()
{
  
  if ( _cursor_x == 0 && _cursor_y > 0 ) {
    _cursor_x = 80;
    _cursor_y -= 1;
  } else if ( _cursor_x > 0 ) {
    _cursor_x -= 1;
  }
  setCursorPosition(_cursor_x, _cursor_y);
}

void advanceCursor()
{
  _cursor_x += 1;
  if ( _cursor_x > 79 ) {
    _cursor_x = 0;
    _cursor_y += 1;
  }
  setCursorPosition(_cursor_x, _cursor_y);
}
