all: boot.img kernel.bin

src/%.o: src/%.c
	bcc -ansi -3 -c -o $@ $<

kernel.bin: src/kernel.o
	ld86 -T0x1000 -M -o $@ $^

asm/kernel_syms.S: kernel.bin
	objdump86 kernel.bin | \
		grep -E "^[0-9]+ T _.*" | \
		python -c "import sys; print '\n'.join([\"_extern_c%s:\n    jmp 0x1000:0x%04x\" % (x.split(' ')[2].strip('\n'), int(x.split(' ')[0].lstrip('0'), 16)-0x1000) for x in sys.stdin.readlines()])" > asm/kernel_syms.S

boot.bin: asm/kernel_syms.S asm/bootloader.S asm/bootloader.S
	cd asm && nasm bootloader.S -f bin -o ../$@

asm/%.o: asm/%.S
	nasm $< -f as86 -o $@

boot.img: boot.bin kernel.bin
	cat $^ > $@

test: boot.img
	bochs -f bochsrc -q

.PHONY: clean
clean:
	rm -f boot.bin asm/*o src/*o
