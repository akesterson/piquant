#!/bin/bash

base=$(objdump -t kernel.elf | grep -E '.d\s+.text' | grep -Eo '^[0-9a-z]+')
#start=$(objdump -t kernel.elf | grep -E 'F\s+.text\s+[0-9a-z]+\s+_start' | grep -Eo '^[0-9a-z]+')

echo > asm/kernel_syms.S

objdump -t kernel.elf | grep -E 'F\s+.text\s+[0-9a-z]+\s+' | (while read LINE;
    do \
	method=$(echo "$LINE" | grep -Eo ' [a-zA-Z0-9_]+$' | cut -d ' ' -f 2); \
	start=$(echo "$LINE" | grep -Eo '^[0-9a-z]+'); \
	hexdiff=$(python -c "print '%x' % (0x${start} - 0x${base})"); \
	echo "_extern_c_${method}:" >> asm/kernel_syms.S; \
	echo "    jmp 0x1000:0x${hexdiff}" >> asm/kernel_syms.S; \
	echo >> asm/kernel_syms.S; \
    done
)
