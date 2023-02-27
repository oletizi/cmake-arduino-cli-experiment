PROJECT_NAME := $(shell cat .project-name)
PROJECT_VERSION := $(shell cat .project-version)
MONITOR_SCRIPT := ./monitor.sh
FIND_PORT_SCRIPT := ./find-port.sh
PORT := $(shell ${FIND_PORT_SCRIPT})
FQBN := --fqbn teensy:avr:teensy41
all: build upload monitor

# runs cmake
cmake:
	mkdir cmake && cd cmake && cmake ..

# builds everything (arduino and native) and runs the test suite
test: build
	cd cmake && make $(PROJECT_NAME)_test && ./test/$(PROJECT_NAME)_test
.PHONY: test

# build the juce target
jucebuild: cmake
	cd cmake && make $(PROJECT_NAME)_juce
.PHONY: jucebuild

# runs the juce program
juce-run: jucebuild
	cd cmake && ./src/$(PROJECT_NAME)_juce_artefacts/$(PROJECT_NAME)_juce

arduinobuild:
	arduino-cli compile --library ./lib/libarduino-dummy/ ${FQBN} .
.PHONY: arduinobuild

# builds everything (arduino and native)
build: jucebuild arduinobuild
.PHONY: build

upload: arduinobuild
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