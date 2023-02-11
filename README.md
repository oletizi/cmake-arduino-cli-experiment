# CMake + Arduino CLI Experiment

Experiment with getting CMake and the Arduino CLI to play nice together.

## Goals:
* A CMake build system for testing and running code on a native system in an IDE.
* A parallel arduino-cli build system to build, upload, and run on arduino boards.

## Prerequisites:
* CMake
* Arduino cli

## Makefile vs. CMake
* Makefile &mdash; The top-level `Makefile` is only for building with `arduino-cli` for a board.
* CMake &mdash; `CMakeLists.txt` files are only for building on the native system and in an IDE. 

Helper scripts:
* `bin/find-port.sh` &mdash; Uses `arduino-cli` to finds the serial port of the board. 
* `bin/monitor.sh` &mdash; monitors output of the board's serial port
