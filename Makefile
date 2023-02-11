.PHONY: all build upload monitor

MONITOR_SCRIPT := ./monitor.sh
FIND_PORT_SCRIPT := ./find-port.sh
PORT := $(shell ${FIND_PORT_SCRIPT})
FQBN := --fqbn teensy:avr:teensy41
all: build upload monitor

build:
	arduino-cli compile ${FQBN} .

upload:
	arduino-cli upload -p $(PORT) ${FQBN} .

monitor:
	${MONITOR_SCRIPT}

board:
	arduino-cli board list

clean:
	arduino-cli cache clean