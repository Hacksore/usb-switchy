#!/bin/bash
arduino-cli core install arduino:avr
arduino-cli core install arduino:samd

arduino-cli compile --fqbn arduino:samd:mkr1000 client/
arduino-cli compile --fqbn arduino:avr:uno host/
