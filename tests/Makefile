%.o: %.c
	gcc -I../src -ansi -Wall -Werror -c -o $@ $<
	for file in $$(cat $$(echo $@ | sed 's/\.o$$//').deps); do \
		gcc -I../src -ansi -Wall -Werror -c -o ./$${file}.o ../src/$$file.c ; \
	done

%.elf: %.o
	gcc -o $@ $^ $$(cat $$(echo $@ | sed 's/\.elf$$//').deps | sed 's/$$/\.o/g')


all_targets:=$(shell ls *c | sed 's/\.c$$/\.elf/g')

all: $(all_targets)

.PHONY: clean
clean:
	rm -f *o
	rm -f *elf
