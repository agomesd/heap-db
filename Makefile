CC = gcc
CFLAGS = -Wall -Wextra -I include

SRC = src/values/values.c src/utils/utils.c src/hashtable/hashtable.c
TEST_SRC = tests/main.c tests/utils/test_utils.c tests/values/test_values.c tests/hashtable/test_hashtable.c

SRC_OBJ = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

TARGET = build/test

all: test

test: $(SRC_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) $^ -o $(TARGET)
	./$(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_OBJ) $(TEST_OBJ) $(TARGET)
