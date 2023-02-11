#!/usr/bin/env sh

arduino-cli board list | grep teensy | cut -d " " -f 1