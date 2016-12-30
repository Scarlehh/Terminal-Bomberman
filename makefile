# Compiler
CC     = gcc
CFLAGS = -lncursesw -pthread -g -I $(LIBS)

MKBIN   = mkdir -p $(BIN)
MKBUILD = mkdir -p $(BUILD)

# Directory Structure
BIN   = bin/
BUILD = build/
LIBS  = include/
SRC   = src/

# Object Files
_OBJ =\
	main.o \
	man.o \
	board.o \
	bomb.o \
	physics.o
OBJ  = $(patsubst %,$(BUILD)%,$(_OBJ))

# Dependencies
DEPS = $(OBJ:.o=.d)

# Main
MAIN = main

# Build executable
.PHONY: default
default: mkdir $(OBJ)
	$(CC) $(OBJ) -o $(BIN)$(MAIN) $(CFLAGS)

-include $(DEPS)

# Build object files
$(BUILD)%.o: $(SRC)%.c
	$(CC) -c $< -MMD -MF $(@:.o=.d) -o $@ $(CFLAGS)
	$(CC) -c $< -o $@ $(CFLAGS)

# Run program
.PHONY: run
run:
	./$(BIN)$(MAIN)

# Build directory structure
.PHONY: mkdir
mkdir:
	$(MKBIN)
	$(MKBUILD)

# Clean up object files
.PHONY: clean
clean:
	$(RM) -r $(BUILD)
	$(RM) -r *~
