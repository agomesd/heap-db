# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -I src -I /usr/local/include/sea-float

# Linker flags
LDFLAGS = -L /usr/local/lib -lsea-float

# Source files (your actual project code)
SRC = src/values/values.c
SRC_OBJ = $(SRC:.c=.o)

# Test files
TEST_SRC = tests/main.c tests/values/test_values.c
TEST_OBJ = $(TEST_SRC:.c=.o)

# Output
TARGET = build/test

# Default
all: test

# Build test executable
test: $(SRC_OBJ) $(TEST_OBJ)
	@mkdir -p build
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $(TARGET)
	@echo "Running tests..."
	./$(TARGET)

# Compile rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(SRC_OBJ) $(TEST_OBJ) $(TARGET)

.PHONY: all test clean
