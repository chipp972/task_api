# author: pierre-charles_nicolas
# last release: 28/03/2016

# directories
LIB_DIR=lib
SRC_DIR=src
INC_DIR=include

# sources
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(SRC:.c=.o)
TARGET=libtask.so

# compiler and flags
CC=gcc
CFLAGS=-Wall -g -I$(INC_DIR) -fPIC
LDFLAGS=-lpthread -lrt -shared -Wl,-soname,$(TARGET) -lc

all: $(LIB_DIR)/$(TARGET)

$(LIB_DIR)/$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	find $(SRC_DIR) -name "*.o" -exec rm -f {} \;
	find $(SRC_DIR) -name "*~" -exec rm -f {} \;

mrproper: clean
	rm -f $(LIB_DIR)/*
