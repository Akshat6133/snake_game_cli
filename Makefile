# Compiler settings
CC = clang
CFLAGS = -Wall
OBJ = main.o
EXEC = snake

# The default target: 'make'
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Rule to compile 'main.c'
main.o: main.c console.h
	$(CC) $(CFLAGS) -c main.c

# Clean up object files and executable
clean:
	rm -f $(OBJ) $(EXEC)

# Rule to make sure the repository is cloned first, before building
prepare: 
	@echo "No external repositories required."



