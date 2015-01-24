resetFloppy:
mov ax, 0                      ; reset floppy disk (only need ah, reset
                               ; al while we're here though)
mov dl, 0                      ; use drive 0 (first floppy)
int 0x13
jc resetFloppy
ret

loadDiskSector:


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
