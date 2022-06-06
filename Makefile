#build
BUILD_DIR	= build
BUILD		= $(BUILD_DIR)/build
LIBS_DIR	= lib
TARGET		= main.c
LIBS		= $(wildcard $(LIBS_DIR)/*.c)
# LIBS		+= $(wildcard $(LIBS_DIR)/**/*.c)
# LIBS		+= $(wildcard $(LIBS_DIR)/**/**/*.c)
# LIBS		+= $(wildcard $(LIBS_DIR)/**/**/**/*.c)
OBJS		= $(patsubst  %, build/%, $(LIBS:.c=.o))
OBJS		+= $(patsubst  %, build/%, $(TARGET:.c=.o))
ASMS		= $(patsubst  %, build/%, $(OBJS:.o=.asm))

# DEFINE
FLAGS		= -D F_CPU=16000000UL
FLAGS		+= -D DEBUG_EN=1
FLAGS 		+= -D BAUD=9600

# DEFINE
PORT		= COM3#					Op welke usb poort je arduino zit
DEVICE		= atmega2560#		Welke chip je arduino heeft
PROGRAMMER	= wiring
BAUD		= 115200
COMPILE		= avr-gcc -Wall -Os -mmcu=$(DEVICE) -std=gnu99

.PHONY: clean upload

default: compile upload monitor

$(BUILD_DIR)/%.asm: %.c
	mkdir -p $(@D)
	$(COMPILE) -S -c $< -o $@

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(COMPILE) $(FLAGS) -c $< -o $@

compile: clean $(OBJS)
	$(COMPILE) -o $(BUILD).elf $(OBJS)
	avr-objcopy -j .text -j .data -O ihex $(BUILD).elf $(BUILD).hex
	avr-size --format=avr --mcu=$(DEVICE) $(BUILD).elf

asm: clean-all $(ASMS)

upload:
	assets\avrdude-v7.0-windows-windows-x86\avrdude.exe -v -V -D -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(BUILD).hex:i

monitor:
	assets\arduino-cli\bin\arduino-cli.exe monitor -p $(PORT)

clean:
	-rm ${BUILD_DIR}/*.o
	-rm ${BUILD_DIR}/*.elf
	-rm ${BUILD_DIR}/*.hex
	-rm ${BUILD_DIR}/*.s
	-rm ${BUILD_DIR}/*.asm

clean-all: 
	-rm -rf ${BUILD_DIR}