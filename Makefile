all: boot.img kernel.bin

boot.bin: asm/bootloader.S asm/bootloader.S
	nasm asm/bootloader.S -f bin -o $@

asm/%.o: asm/%.S
	nasm $< -f as86 -o $@

src/%.o: src/%.c
	bcc -ansi -3 -c -o $@ $<

kernel.bin: src/kernel.o
	ld86 -T0x1000 -o $@ $^

boot.img: boot.bin kernel.bin
	cat $^ > $@

test: boot.img
	bochs -f bochsrc -q

.PHONY: clean
clean:
	rm -f boot.bin asm/*o src/*o
