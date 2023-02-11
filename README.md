# CMake + Arduino CLI Experiment

Experiment with getting CMake and the Arduino CLI to play nice together.

Goals:
* A CMake build system for testing and running code on a native system in an IDE.
* A parallel arduino-cli build system to build, upload, and run on arduino boards.

Prerequisites:
* CMake
* Arduino cli

Helper scripts:
* `find-port.sh` &mdash; Uses `arduino-cli` to finds the serial port of the board. 
* `monitor.sh` &mdash; monitors output of the board's serial port
