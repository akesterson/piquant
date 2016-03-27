ifeq ($(TEST_FORMAT),)
	TEST_FORMAT:=tunit
endif

all: boot.img kernel.bin

src/%.o: src/%.c
	bcc -ansi -0 -c -o $@ $<

kernel.bin: src/screen.o src/conio.o src/string.o src/stdlib.o src/basic.o src/kernel.o
	ld86 -d -M -o $@ $^ | tee ld86.out

asm/kernel_syms.S: kernel.bin
	cat ld86.out | \
		grep -E "^\s+kernel\s+[a-zA-Z0-9_]+  0  [0-9]+" | \
		python -c "import sys; print '\n'.join([\"_extern_c%s:\n    jmp 0x1000:0x%04x\" % (x.lstrip(' ').replace('kernel', '').lstrip(' ').split(' ')[0], int(x.lstrip(' ').replace('kernel', '').lstrip(' ').split(' ')[4], 16)) for x in sys.stdin.readlines()])" > asm/kernel_syms.S

boot.bin: asm/kernel_syms.S asm/bootloader.S asm/bootloader.S
	cd asm && nasm bootloader.S -f bin -o ../$@

asm/%.o: asm/%.S
	nasm $< -f as86 -o $@

boot.img: boot.bin kernel.bin
	dd if=/dev/zero of=boot.img ibs=1k count=1440
	cat $^ > boot.tmp
	dd if=boot.tmp of=boot.img conv=notrunc
	rm -f boot.tmp

run: boot.img
	bochs -f bochsrc -q

.PHONY: test
test:
	cd tests && make clean && ../dependencies/bin/shunit.sh -f $(TEST_FORMAT) -t test.sh

.PHONY: clean
clean:
	rm -f boot.bin asm/*o src/*o
