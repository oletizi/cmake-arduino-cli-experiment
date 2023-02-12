PROJECT_NAME := $(shell cat .project-name)
PROJECT_VERSION : $(shell cat .project-version)
MONITOR_SCRIPT := ./monitor.sh
FIND_PORT_SCRIPT := ./find-port.sh
PORT := $(shell ${FIND_PORT_SCRIPT})
FQBN := --fqbn teensy:avr:teensy41
all: build upload monitor

cmake:
	mkdir cmake && cd cmake && cmake ..

test: cmake
	cd cmake && make $(PROJECT_NAME)_test && ./test/$(PROJECT_NAME)_test
.PHONY: test

juce: cmake
	cd cmake && make $(PROJECT_NAME)_juce
.PHONY: juce

# run the juce program
juce-run: juce
	cd cmake && ./src/$(PROJECT_NAME)_juce_artefacts/$(PROJECT_NAME)_juce

# builds the juice thingy and the arduino thingy
build: juce
	arduino-cli compile ${FQBN} .
.PHONY: build

upload:
	arduino-cli upload -p $(PORT) ${FQBN} .
.PHONY: upload

monitor:
	${MONITOR_SCRIPT}
.PHONY: monitor

board:
	arduino-cli board list
.PHONY: board

clean:
	arduino-cli cache clean
	rm -rf cmake
.PHONY: clean