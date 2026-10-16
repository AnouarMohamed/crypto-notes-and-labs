CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic -O2 -Iinclude
SRC_DIR = src
OBJ_DIR = build
TEST_DIR = tests

LIB_SRCS = $(SRC_DIR)/caesar.c $(SRC_DIR)/vigenere.c
LIB_OBJS = $(OBJ_DIR)/caesar.o $(OBJ_DIR)/vigenere.o

.PHONY: all clean test demo

all: demo test

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

demo: $(LIB_OBJS) $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) $(SRC_DIR)/main.c $(LIB_OBJS) -o $(OBJ_DIR)/tp01_demo

$(OBJ_DIR)/test_caesar: $(LIB_OBJS) $(TEST_DIR)/test_caesar.c
	$(CC) $(CFLAGS) $(TEST_DIR)/test_caesar.c $(LIB_OBJS) -o $@

$(OBJ_DIR)/test_vigenere: $(LIB_OBJS) $(TEST_DIR)/test_vigenere.c
	$(CC) $(CFLAGS) $(TEST_DIR)/test_vigenere.c $(LIB_OBJS) -o $@

test: $(OBJ_DIR)/test_caesar $(OBJ_DIR)/test_vigenere
	@echo "===== Caesar tests ====="
	@$(OBJ_DIR)/test_caesar
	@echo
	@echo "===== Vigenere tests ====="
	@$(OBJ_DIR)/test_vigenere

clean:
	rm -rf $(OBJ_DIR)
