[![Build Status](https://travis-ci.org/akesterson/piquant.svg?branch=master)](https://travis-ci.org/akesterson/piquant)

Piquant
====

Piquant is a little toy operating system I'm building.

Why?
=====

Because it's fun. Don't you like to have fun? Ogre.

What does it do?
=====

Right now, not much of anything at all. It boots from a 1.44mB floppy disk, and enters into a BASIC interpreter, just like your favorite home computers of the 70s/80s!

![Image of Piquant v0.1](media/screenshot.png)

Currently the BASIC only understands simple, 1-digit arithmetic expressions. But this will soon change; I intend to implement at least as many features as uBASIC, maybe QuickBASIC eventually.

How can I run it?
=====

You have to build it to run it. To build it, you need:

* bcc (bruce's c compiler - check your OS's package repositories)
* nasm
* gnu make
* ld86, objdump86, as86

To run it, you can use anything, but the makefile assumes you have 'bochs' installed.

    make clean run

This will rebuild all of the sources and fire up the bochs emulator. Have fun.

Developing & Testing
=======

You need gcc to run the unit tests. To run the unit tests:

    make test

Keep in mind that the unit tests are compiled with gcc, not bcc, as I couldn't find an elegant way to make bcc produce objects that could easily be run in linux (especially Travis-CI). So while the tests are an accurate test of the C code under ANSI spec, they make no promises re: what bcc is eventually going to do with that code.

New unit tests are created by making a new *.c file in tests/. Drop the name of whatever portions of piquant it relies on into a '.deps' file. Look at the others for examples.