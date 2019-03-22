#
# File Name: makefile
# Author: Seree Rakwong
# Date: 28-NOV-2017
#

TARGET = tui_test
CC     = gcc
CFLAGS = -g -Wall
LFLAGS = -lm -lcurses

.PHONY: default all clean

default: $(TARGET)
all: default

BIN_DIR  = ./bin
SRC_DIR  = ./src
INC_DIR  = ./include
SOURCES  = $(SRC_DIR)/tui.c \
           $(SRC_DIR)/tuidc.c \
           $(SRC_DIR)/tuistc.c \
           $(SRC_DIR)/tuiedt.c \
           $(SRC_DIR)/tuibtn.c \
           $(SRC_DIR)/tuilb.c \
           $(SRC_DIR)/tuilctl.c \
           $(SRC_DIR)/tuifrmwnd.c \
           $(SRC_DIR)/tui_test.c


OBJECTS  = $(SOURCES:.c=.o)
INCLUDES = -I$(INC_DIR)
DEFINES  = -D__UNIX__ -D__LINUX__


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

clean:
	rm -f src/*.o $(TARGET)*


