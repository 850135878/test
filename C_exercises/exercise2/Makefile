CC = gcc
CFLAGS = -fPIC -Wall -Iinclude/cal -Iinclude/data_structures -Iinclude/tools  
LDFLAGS = -shared
RM = rm -r

# Define library name and version
LIB_NAME = calculators
LIB_VERSION = 1.0.0
LIB_LINK = lib$(LIB_NAME).so
LIB_SONAME = lib$(LIB_NAME).so.$(shell echo $(LIB_VERSION) | cut -d'.' -f1)

LIB_TARGET = lib$(LIB_NAME).so.$(shell echo $(LIB_VERSION) | tr '.' '_')
TARGET = main


# Source directories
SRC_MAIN_DIR = src
SRC_LIB_DIRS = src/cal src/data_structures src/tools


# Directory for library and binaries
LIB_DIR = lib
BIN_DIR = bin
OBJ_DIR = obj

# Source and Object files
SRC_LIB_FILES = $(foreach dir,$(SRC_LIB_DIRS),$(wildcard $(dir)/*.c))
SRC_MAIN_FILE = $(wildcard $(SRC_MAIN_DIR)/*.c)

LIB_OBJS = $(patsubst src/%.c,obj/%.o,$(SRC_LIB_FILES))
MAIN_OBJ = $(patsubst src/%.c,obj/%.o,$(SRC_MAIN_FILE))

$(shell mkdir -p $(sort $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR) $(dir $(LIB_OBJS))))

all: $(LIB_DIR)/$(LIB_LINK) $(BIN_DIR)/$(TARGET)

# Link dynamic library
$(LIB_DIR)/$(LIB_LINK): $(LIB_OBJS)
	$(CC) $(LDFLAGS) -o $@ -Wl,-soname,$(LIB_SONAME) $^ 
	ln -sf $(LIB_LINK) $(LIB_DIR)/$(LIB_SONAME)
	ln -sf $(LIB_LINK) $(LIB_DIR)/$(LIB_TARGET)

# Compile library object files
$(OBJ_DIR)/%.o: $(SRC_MAIN_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< 

# Link executable
$(BIN_DIR)/$(TARGET): $(MAIN_OBJ) $(LIB_DIR)/$(LIB_LINK) 
	$(CC) $(CFLAGS) -o $@ $< -L$(LIB_DIR) -l$(LIB_NAME) -lm

.PHONY: all clean
clean:
	-$(RM) $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR)

.DEFAULT_GOAL := all
