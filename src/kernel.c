char _cursor_x = 0;
char _cursor_y = 0;

#define NULL 0x0
typedef int size_t;

void setCursorPosition(char x, char y)
{
#asm
  push bx;
  mov bx, sp;
  mov dl, [bx+4];
  mov dh, [bx+6];
  pop bx;
  push ax;
  push bx;
  mov ah, #0x02;
  mov bx, #0x0;
  int 0x10;
  pop bx;
  pop ax;
#endasm
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

void putc(char c)
{
#asm
  push bx;
  push ax;
  mov bx, sp;
  mov al, [bx+6];
  mov ah, #0x0e;
  mov bh, #0x00;
  mov bl, #0x07;
  int 0x10;
  pop ax;
  pop bx;
#endasm
    return;
}

int strlen(char *ptr)
{
  char *ptr2 = ptr;
  if ( ptr == NULL ) {
    return 0;
  }

  while (*ptr2 != 0x0 ) {
    ptr2 += 1;
  }

  return ptr2 - ptr;
}

void puts(char *ptr, char x, char y) 
{
  if ( ptr == NULL ) {
    return;
  }
  while ((char)*ptr != 0x0) { 
    putc((char)*ptr);
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

char getkey(char *dest)
{
  char echo;
  char scancode;
#asm
  push ax;
  mov ah, 0x10;
  int 0x16;
  mov [bp-6], ah;
  mov [bp-5], al;
  pop ax;
#endasm
  *dest = echo;
  return scancode;
}

char *gets(char *d)
{
  char *orig = d;
  char scancode;
  char printable;

  if ( d == NULL ) {
    return NULL;
  }

  scancode = getkey(&printable);

  while ( scancode != NULL ) {
    if ( scancode == 0x0e ) {
      if ( d > orig ) {
	backupCursor();
	setCursorPosition(_cursor_x, _cursor_y);
	d -= 1;
	putc(0x0);
      }
    } else if ( scancode == 0x1c ) {
      break;
    } else {
      *(d++) = printable;
      putc(printable);
      advanceCursor();
    } 
    scancode = getkey(&printable);
  }
  
 _gets_finish_loop:
  *d = NULL;
  return orig;
}

void memset(void *s, int c, size_t n)
{
  int *d = (int *)s;
  if ( s == NULL ) {
    return;
  }
  while ( ((int)d - (int)s) <= n ) {
    *d = c;
    d += sizeof(int);
  }
}

signed int strcmp(char *s1, char *s2)
{
  int d = 0;
  int s1len = 0;

  if ( s1 == NULL || s2 == NULL ) {
    return 1;
  }

  s1len = strlen(s1);
  if ( s1len != strlen(s2) ) {
    return 1;
  }

  while ( *s1 != '\0' ) {
    if ( *s1 != *s2 ) {
      return 1;
    }
    s1 += sizeof(char);
    s2 += sizeof(char);
  }

  return 0;
}

void repl(void)
{
  char keybuff[512];

  while ( 1 ) {
    puts("> ");
    memset((void *)&keybuff, 0x00, 512);
    if ( gets((char *)&keybuff) != NULL ) {
      puts("\n");
      if ( strcmp(&keybuff, "quit") == 0 ) {
	puts("You asked for it\n");
	#asm
	hlt;
	#endasm

      } else if ( strcmp(&keybuff, "reset") == 0 ) {
	puts("Resetting PC ... ");
	#asm
	jmp 0xf000:0xfff0;
	#endasm

      } else if ( strcmp(&keybuff, "help") == 0 ) {
	puts("help : Show this help message\n");
	puts("quit : Halt the computer\n");
	puts("reset : Reset the PC\n");
	puts("\n");
      } else {
	puts("Wat?\n");
      }
    }
  }
}

void blankScreen(void)
{
  char i = 0;
  char j = 0;
  for ( i = 0 ; i < 26 ; i++ ) {
    for ( j = 0; j < 81 ; j++ ) {
      setCursorPosition(j, i);
      putc(' ');
    }
  }
}

void main(void)
{
  blankScreen();
  setCursorPosition(0, 0);
  puts("Piquant Kernel v0.1\n");
  puts("\n");
  repl();
}
