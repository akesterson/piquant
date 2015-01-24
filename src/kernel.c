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
  while (*ptr != '\0') { 
    printChar(*ptr);
    *ptr++;
  }

  return;
}

void main(void)
{
  char *kernelHello = "Welcome to Piquant, please wait while Kernel boots...\n";
  printString(kernelHello);
  while(1);
}
