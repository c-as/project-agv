rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

#build
BUILD_DIR	= build
BUILD		= $(BUILD_DIR)/build
LIBS_DIR	= lib
TARGET		= main.c
LIBS		= $(call rwildcard,$(LIBS_DIR)/,*.c)
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
	@echo \###########################################################################
	@echo Makefile: $< compilen...
	@echo \###########################################################################
	mkdir -p $(@D)
	$(COMPILE) $(FLAGS) -c $< -o $@

compile: clean $(OBJS)
	@echo \###########################################################################
	@echo Makefile: Objecten linken...
	@echo \###########################################################################
	$(COMPILE) -o $(BUILD).elf $(OBJS)
	avr-objcopy -j .text -j .data -O ihex $(BUILD).elf $(BUILD).hex
	avr-size --format=avr --mcu=$(DEVICE) $(BUILD).elf
	@echo \###########################################################################
	@echo Makefile: Compileren voltooid...
	@echo \###########################################################################

asm: clean-all $(ASMS)

upload:
	@echo \###########################################################################
	@echo Makefile: Uploaden op poort: ${PORT}...
	@echo \###########################################################################
	assets\avrdude-v7.0-windows-windows-x86\avrdude.exe -v -V -D -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(BUILD).hex:i
	@echo \###########################################################################
	@echo Makefile: Uploaden voltooid.
	@echo \###########################################################################

monitor:
	@echo \###########################################################################
	@echo Makefile: Monitor starten...
	@echo \###########################################################################
	assets\arduino-cli\bin\arduino-cli.exe monitor -p $(PORT)

clean:
	@echo \###########################################################################
	@echo Makefile: Oude bestanden verwijderen...
	@echo \###########################################################################
	-rm ${BUILD_DIR}/*.o
	-rm ${BUILD_DIR}/*.elf
	-rm ${BUILD_DIR}/*.hex
	-rm ${BUILD_DIR}/*.s
	-rm ${BUILD_DIR}/*.asm

clean-all: 
	@echo \###########################################################################
	@echo Makefile: Map: $(BUILD_DIR)/ verwijderen...
	@echo \###########################################################################
	-rm -rf $(BUILD_DIR)