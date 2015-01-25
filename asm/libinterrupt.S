resetFloppy:
	mov ah, 0                      ; reset floppy disk
	mov dl, 0                      ; use drive 0 (first floppy)
	int 0x13	
	jc resetFloppy
	ret

	;; set al = how many sectors to read
	;; set ch = what track to read from
	;; set cl = what sector on the track to start reading
	;; set es:bx = where to store the disk data
loadFloppyDiskSectors:
	mov ah, 0x02		; int 0x13 function 2 (read sectors from disk)
	mov dh, 0		; head 0 (assume simple small floppy)
	mov dl, 0		; drive 0 = floppy drive
	int 0x13
	jc loadFloppyDiskSectors ; retry on errors (not much else we can do)

blankScreen:
	push cx
	mov cx, 0x0
_blankScreen_next:
	mov al, 0x20            ; blank space
	call printCharacter
	inc cx
	cmp cx, 0x7d0		; 80 * 25 screen = 0x7d0
	jne _blankScreen_next
_blankScreen_exit:
	pop cx
	ret
	
	;; set dh = row
	;; set dl = column
setCursorPosition:
	mov ah, 0x02
	mov bh, 0
	int 0x10
	ret
	
	;;  set al = character to display
printCharacter:                 ; print a single character to the display
	mov ah, 0x0e            ; int 0x10 is the entire display control, 
				; 0x0e means teletype output
	mov bh, 0x00		; Print on the zero (primary) page
	mov bl, 0x07		; Color. 0x07 is grey on black.
	int 0x10
	ret

	;;  set si = string to display
printString:                   ; print the entire string pointed to by si
_printString_next:
	mov al, [si]                   ; [x] == *x, dereferencing source index
	cmp al, 0x0                    ; found the trailing NULL?
	je _printString_exit
	call printCharacter
	inc si
	jmp _printString_next
_printString_exit:
	ret
