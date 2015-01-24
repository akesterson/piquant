[BITS 16]	               ; 16 bit real mode code
[ORG 0x7C00]                   ; Origin at 0x7C00 (upper end of memory)

JMP $                          ; hang forever

TIMES 510 - ($ - $$) db 0      ; fill up to 510 bytes with 0
DW 0xAA55                      ; magic bootloader signature