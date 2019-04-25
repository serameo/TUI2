#
# File Name: makefile
# Author: Seree Rakwong
# Date: 28-NOV-2017
#

TARGET = tui_test_linux
CC     = gcc
CFLAGS = -g -Wall -m32
LFLAGS = -lm -lcurses -lpthread

.PHONY: default all clean

default: $(TARGET)
all: default

BIN_DIR  = ./bin
SRC_DIR  = ./src
INC_DIR  = ./include
SOURCES  = $(SRC_DIR)/tui_node.c \
           $(SRC_DIR)/tui_list.c \
           $(SRC_DIR)/tui_stack.c \
           $(SRC_DIR)/tui_queue.c \
           $(SRC_DIR)/tui_tree.c \
           $(SRC_DIR)/tui_dic.c \
           $(SRC_DIR)/tui_xcnf.c \
           $(SRC_DIR)/tuithrd.c \
           $(SRC_DIR)/tui.c \
           $(SRC_DIR)/tuidc.c \
           $(SRC_DIR)/tuistc.c \
           $(SRC_DIR)/tuiedt.c \
           $(SRC_DIR)/tuibtn.c \
           $(SRC_DIR)/tuilb.c \
           $(SRC_DIR)/tuilctl.c \
           $(SRC_DIR)/tuitctl.c \
           $(SRC_DIR)/tuifrmwnd.c \
           $(SRC_DIR)/tuiddx.c \
           $(SRC_DIR)/tui_test.c


OBJECTS  = $(SOURCES:.c=.o)
INCLUDES = -I$(INC_DIR)
DEFINES  = -D__UNIX__ -D__LINUX__ -D__USE_CURSES__


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

clean:
	rm -f src/*.o $(TARGET)*


