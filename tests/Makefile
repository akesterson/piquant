CFLAGS:=-ffreestanding -fno-builtin -I../src -ansi -Wall -Werror

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<
	for file in $$(cat $$(echo $@ | sed 's/\.o$$//').deps); do \
		gcc $(CFLAGS) -c -o ./$${file}.o ../src/$$file.c ; \
	done

%.elf: %.o
	gcc $(CFLAGS) -o $@ $^ $$(cat $$(echo $@ | sed 's/\.elf$$//').deps | sed 's/$$/\.o/g')


all_targets:=$(shell ls *c | sed 's/\.c$$/\.elf/g')

all: $(all_targets)

.PHONY: clean
clean:
	rm -f *o
	rm -f *elf
