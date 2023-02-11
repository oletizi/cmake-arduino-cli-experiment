.PHONY: all build upload monitor

MONITOR_SCRIPT := ./monitor.sh
FIND_PORT_SCRIPT := ./find-port.sh
PORT := $(shell ${FIND_PORT_SCRIPT})

all: build upload monitor

build:
	arduino-cli compile --fqbn teensy:avr:teensy41 .

upload:
	arduino-cli upload -p $(PORT) --fqbn teensy:avr:teensy41 .

monitor:
	${MONITOR_SCRIPT}

board:
	arduino-cli board list