#include "screen.h"
#include "string.h"
#include "conio.h"
#include "basic.h"

void _start(void)
{
  while ( 1 ) {
  };
  blankScreen();
  setCursorPosition(0, 0);
  _cputs("Piquant Basic v0.1\n\n");
  //basic_repl();
}
