Piquant
====

Piquant is a little toy operating system I'm building.

Why?
=====

Because it's fun. Don't you like to have fun? Ogre.

What does it do?
=====

Right now, not much of anything at all. It boots from a 1.44mB floppy disk, throws some text to the screen, and enters a primitive REPL (where you can do nothing but display a help message, HALT the machine, or RESET the machine).

![Image of Piquant v0.1](media/screenshot.png)

I think I'm going to expand the basic REPL into a BASIC interpreter, just like the classic machines of the 80s. "Operating System? Oh, you mean the BASIC ROM, right?" :)

How can I run it?
=====

You have to build it to run it. To build it, you need:

* bcc (bruce's c compiler - check your OS's package repositories)
* nasm
* gnu make
* ld86, objdump86, as86

To run it, you can use anything, but the makefile assumes you have 'bochs' installed.

    make clean test

This will rebuild all of the sources and fire up the bochs emulator. Have fun.