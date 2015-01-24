[bits 16]	               ; 16 bit real mode code
[org 0x7C00]                   ; Origin at 0x7C00 (upper end of memory)

start:
	mov si, _str_hello     ; si = source index
	call printString
	mov al, 0x97
	call printCharacter

; 	mov al, 0x17           ; read the remaining 16 tracks 
; 	mov ch, 0x1            ; .... on track 1 ....
; 	mov cl, 0x2            ; .... starting at sector 2
; 	mov bx, 0x1000         ; 0x1000 is a standard kernel start location
; 	mov es, bx
; 	xor bx                 ; bx = 0, es:bs = 0x1000:0
; 	call loadFloppyDiskSectors
; 	push ax
; 	mov ax, bx
; 	add ax, 0x2200         ; we just read 0x2200 bytes, move pointer in memory
; 	mov bx, ax
; 	pop ax
; 	mov al, 0x17           ; read 18 sectors per track for all future tracks
;         mov cl, 0x1            ; start at sector 1 for all future tracks

; 	mov di, 0x2            ; abuse di as a counter, while (di < 80)
;                                ; di is technically a destination index for stream
; 	                       ; ops, but nothing is using it ATM, so gimme.
; _next_floppy_track:
; 	mov ch, di
; 	call loadFloppyDiskSectors
; 	push ax
; 	mov ax, bx
; 	add ax, 0x2400         ; each floppy track is (512b*18s)=0x2400 bytes long
; 	mov bx, ax
; 	pop ax
; 	inc di
; 	push cx
; 	mov cx, 0x50
; 	cmp di, cx           ; di < 80 ?
; 	jlt _next_floppy_track

	mov si, _str_floppydone
	call printString
	jmp $

%include "libinterrupt.S"

	_str_hello db 'Piquant v0.1 Bootloader', 0xA, 0
	_str_floppydone db 'Kernel loaded', 0xA, 0

times 510 - ($ - $$) db 0      ; fill up to 510 bytes with 0
dw 0xAA55                      ; magic bootloader signature