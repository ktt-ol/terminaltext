ARDUINO_DIR  = ../Arduino.app/Contents/Resources/Java

TARGET       = CLItest
ARDUINO_LIBS = LiquidCrystal

BOARD_TAG    = uno
ARDUINO_PORT = /dev/cu.usb*

include ../arduino.mk/Arduino.mk


ktt_text.h: figlet_array.py
	python $^ > $@