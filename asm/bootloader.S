[bits 16]	               ; 16 bit real mode code
[org 0x7C00]                   ; Origin at 0x7C00 (upper end of memory)

start:
	;; FIXME - we need to relocate ourselves to the
	;; upper end of memory somewhere so we can overwrite
	;; ourselves with the kernel at 0x0000
	
	call blankScreen

	mov dx, 0x0
	call setCursorPosition
	
	mov si, _str_hello     ; si = source index
	call printString
	mov dh, 0x1
	mov dl, 0x0
	call setCursorPosition
	
	mov al, 0x10           ; read the remaining 16 tracks 
	mov ch, 0x0            ; .... on track 0 ....
	mov cl, 0x2            ; .... starting at sector 2
	mov bx, 0x1000         ; Load the kernel into the bottom of memory
	mov es, bx
	mov bx, 0x0            ; bx = 0, es:bx = 0x1000:0
	call loadFloppyDiskSectors
;; 	push ax	
;; 	mov ax, bx
;; 	add ax, 0x2200         ; we just read 0x2200 bytes, move pointer in memory
;; 	mov bx, ax
;; 	pop ax
;; 	mov al, 0x17           ; read 18 sectors per track for all future tracks
;;         mov cl, 0x1            ; start at sector 1 for all future tracks

;; 	mov di, 0x2FF          ; abuse di as a counter, while (di < 80)
;;                                ; di is technically a destination index for stream
;; 	                       ; ops, but nothing is using it ATM, so gimme.
;; _next_floppy_track:
;; 	push ax
;; 	mov ax, 0x2e
;; 	call printCharacter
;; 	mov ax, cx
;; 	mov cx, di
;; 	mov cl, al
;; 	pop ax
;; 	call loadFloppyDiskSectors
;; 	push ax
;; 	mov ax, bx
;; 	add ax, 0x2400         ; each floppy track is (512b*18s)=0x2400 bytes long
;; 	mov bx, ax
;; 	pop ax
;; 	inc di
;; 	push cx
;; 	mov cx, 0x50
;; 	cmp di, cx             ; di < 80 ?
;; 	jg _end_floppy_read
;; 	pop cx

_end_floppy_read:	
	mov dh, 0x1
	mov dl, 0x0
	call setCursorPosition
	mov si, _str_floppydone
	call printString
	mov ax, 0x1000
	mov ds, ax
	mov ax, 0x1000
	mov ss, ax
	mov sp, 0xFFFF
	jmp _extern_c__start

%include "libinterrupt.S"
%include "kernel_syms.S"
	
	_str_hello db 'Piquant v0.1 Bootloader', 0xA, 0
	_str_loading db 'Loading', 0
	_str_floppydone db 'Kernel loaded', 0xA, 0

times 510 - ($ - $$) db 0      ; fill up to 510 bytes with 0
dw 0xAA55                      ; magic bootloader signature
