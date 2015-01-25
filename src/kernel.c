void printChar(char c)
{
#asm
#if !__FIRST_ARG_IN_AX__
  mov bx, sp
#endif
#if __FIRST_ARG_IN_AX__
  mov si, ax
#else
  mov si, [bx+2]
#endif
    mov ah, 0x0e
    mov bh, 0x00
    mov bl, 0x07
    int 0x10
#endasm
    return;
}

void printString(char *ptr) 
{
  while ((char)*ptr != '\0') { 
    printChar((char)*ptr);
    ptr++;
  }

  return;
}

void main(void)
{
  //printString("Piquant Kernel v0.1\n");
  while(1);
}
