MCU=attiny85
F_CPU=8000000UL
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=gnu++17 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
PORT=/dev/ttyACM0
TARGET=main
SRCS=source-code/main.cpp
PROGRAMMER=avrisp

build:
	${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex
flash:
	${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex
	avrdude -v -c ${PROGRAMMER} -p ${MCU} -P ${PORT} -b 19200 -U flash:w:./${TARGET}.hex:i
