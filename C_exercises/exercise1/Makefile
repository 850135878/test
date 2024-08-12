CC = gcc
CFLAGS = -Wall
RM = rm -r

SRC_MAIN_DIR = src
SRC_MAIN_FILE = $(wildcard $(SRC_MAIN_DIR)/*.c)

OBJ_DIR = obj
MAIN_OBJ = $(patsubst $(SRC_MAIN_DIR)/%.c,$(OBJ_DIR)/src/%.o,$(SRC_MAIN_FILE))

BIN_DIR = bin
TARGET = main

$(shell mkdir -p $(sort $(OBJ_DIR)/src $(BIN_DIR)))

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/src/%.o: $(SRC_MAIN_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: all clean

clean:
	-$(RM) $(OBJ_DIR) $(BIN_DIR)

.DEFAULT_GOAL := all
