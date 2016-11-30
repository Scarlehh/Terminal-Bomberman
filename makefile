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
_DEPS=
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

$(BUILD)%.o: $(SRC)%.c
	$(CC) -c $< -o $@ $(CFLAGS)

run:
	./$(BIN)$(MAIN)

mkdir:
	$(MKBIN)
	$(MKBUILD)

clean:
	$(RM) -r $(BUILD)
	$(RM) -r *~
