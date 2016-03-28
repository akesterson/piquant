ifeq ($(TEST_FORMAT),)
	TEST_FORMAT:=tunit
endif

all: boot.img kernel.bin

src/%.o: src/%.c
	gcc -c -m32 -masm=intel -ffreestanding -Wall -o $@ $<

kernel.elf: src/screen.o src/conio.o src/string.o src/stdlib.o src/basic.o src/kernel.o
	ld -static -nostdlib --nmagic -m elf_i386 -o $@ $^

kernel.bin: kernel.elf
	objcopy -O binary kernel.elf kernel.bin

asm/kernel_syms.S: kernel.bin
	./mk_kernel_syms.sh

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
	cd tests && make clean && ../dependencies/bin/shunit.sh -f $(TEST_FORMAT) -t test.sh ; exit $$?

.PHONY: clean
clean:
	rm -f boot.bin kernel.elf kernel.bin asm/*o src/*o
