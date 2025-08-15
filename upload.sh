#!/bin/bash
BOARD="arduino:avr:mega"
PORT="/dev/ttyACM0"
SKETCH="/home/enrique/Documents/Hydrus/Hydrus/Hydrus.ino"

arduino-cli compile --upload -p /dev/ttyACM0 --fqbn arduino:avr:mega Hydrus.ino
