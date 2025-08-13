#!/bin/bash
BOARD="arduino:avr:mega"
PORT=""
SKETCH=$1

arduino-cli compile --upload -p $PORT --fqbn $BOARD $SKETCH
