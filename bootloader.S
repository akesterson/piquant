[bits 16]	               ; 16 bit real mode code
[org 0x7C00]                   ; Origin at 0x7C00 (upper end of memory)

mov si, _str_hello             ; si = source index
call printString
jmp $                          ; hang forever

printCharacter:                ; print a single character to the display
mov ah, 0x0e                   ; int 0x10 is the entire display control, 
	                       ; 0x0e means teletype output
mov bh, 0x00                   ; Print on the zero (primary) page
mov bl, 0x07                   ; Color. 0x07 is grey on black.
int 0x10
ret

printString:                   ; print the entire string pointed to by si
mov al, [si]                   ; [x] == *x, dereferencing source index
call printCharacter
inc si
cmp al, 0x0                    ; found the trailing NULL?
jne printString
ret


_str_hello db 'Piquant v0.1 Bootloader', 0 ; String + trailing NULL

times 510 - ($ - $$) db 0      ; fill up to 510 bytes with 0
dw 0xAA55                      ; magic bootloader signature