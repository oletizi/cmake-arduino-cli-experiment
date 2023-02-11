.PHONY: all build upload monitor

PORT := $(shell ./bin/find-port.sh)

all: build upload monitor

build:
	arduino-cli compile --fqbn teensy:avr:teensy41 .

upload:
	arduino-cli upload -p $(PORT) --fqbn teensy:avr:teensy41 .

monitor:
	./bin/monitor.sh

board:
	arduino-cli board list