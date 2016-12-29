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

# Object Files
_OBJ=\
	main.o \
	man.o \
	board.o \
	bomb.o \
	physics.o
OBJ = $(patsubst %,$(BUILD)%,$(_OBJ))

DEPS = $(OBJ:.o=.d)

MAIN = main

.PHONY: default
default: mkdir $(OBJ)
	$(CC) $(OBJ) -o $(addprefix $(BIN),$(MAIN)) $(CFLAGS)

-include $(DEPS)

$(BUILD)%.o: $(SRC)%.c
	$(CC) -c $< -MMD -MF $(patsubst %.o,%.d,$@) -o $@ $(CFLAGS)
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: run
run:
	./$(BIN)$(MAIN)

.PHONY: mkdir
mkdir:
	$(MKBIN)
	$(MKBUILD)

.PHONY: clean
clean: $(SRC)main.c
	$(RM) -r $(BUILD)
	$(RM) -r *~
