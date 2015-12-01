#!/usr/bin/env bash
simulavr -d at90can128 -f build/test/TestBuild.elf -W 0x20,testo.log -R 0x22,- -T exit -g &
#ddd --debugger avr-gdb
nemiver
