# Compiler
CC=gcc
CFLAGS=-lncursesw -pthread -g -I $(LIBS)

MKBIN = mkdir -p $(BIN)
MKBUILD = mkdir -p $(BUILD)

# Directory Structure
BIN = bin/
BUILD = build/
LIBS = include/
SRC = src/

# Header files
_DEPS=\
	man.h \
	board.h \
	bomb.h \
	physics.h
DEPS = $(patsubst %,$(LIBS)%,$(_DEPS))

# Object Files
_OBJ=\
	main.o \
	man.o \
	board.o \
	bomb.o \
	physics.o
OBJ = $(patsubst %,$(BUILD)%,$(_OBJ))

MAIN = main

default: mkdir $(OBJ)
	$(CC) $(OBJ) -o $(addprefix $(BIN),$(MAIN)) $(CFLAGS)

$(BUILD)%.o: $(SRC)%.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

run:
	./$(BIN)$(MAIN)

mkdir:
	$(MKBIN)
	$(MKBUILD)

.PHONY: clean

clean:
	$(RM) -r $(BUILD)
	$(RM) -r *~
