#!/usr/bin/env bash
simulavr -d at90can128 -g --writetopipe 0x20,testo.log&
ddd --debugger avr-gdb
