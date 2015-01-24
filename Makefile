all: boot.img

boot.bin: bootloader.S
	nasm $< -f bin -o $@

boot.img: boot.bin
	dd if=$< bs=512 of=$@

test: boot.img
	bochs -f bochsrc -q

.PHONY: clean
clean:
	rm -f boot.bin
