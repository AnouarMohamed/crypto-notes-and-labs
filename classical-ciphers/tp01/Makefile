CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic -O2 -Iinclude

SRC_DIR  := src
OBJ_DIR  := build
TEST_DIR := tests

# Auto-discover library sources (everything in src/ except main.c)
LIB_SRCS := $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
LIB_OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(LIB_SRCS))

# Auto-discover test sources and derive binary names
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_BINS := $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%, $(TEST_SRCS))

DEMO_BIN := $(OBJ_DIR)/tp01_demo
MAIN_OBJ := $(OBJ_DIR)/main.o

.PHONY: all test run clean help

# Default: build everything without running tests
all: $(DEMO_BIN) $(TEST_BINS)

# Create build dir if needed
$(OBJ_DIR):
	mkdir -p $@

# Compile any .c from src/ into a .o (covers lib files and main.c)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link the demo binary
$(DEMO_BIN): $(MAIN_OBJ) $(LIB_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Link each test binary — explicit test_% rule prevents pattern ambiguity
$(OBJ_DIR)/test_%: $(TEST_DIR)/test_%.c $(LIB_OBJS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# Build and run all tests
test: $(TEST_BINS)
	@for bin in $(TEST_BINS); do \
		echo "===== $$(basename $$bin) ====="; \
		$$bin; \
		echo; \
	done

# Build and run the demo
run: $(DEMO_BIN)
	@$(DEMO_BIN)

clean:
	rm -rf $(OBJ_DIR)

help:
	@echo "Targets:"
	@echo "  all    - Build demo and test binaries (default)"
	@echo "  test   - Build and run all tests"
	@echo "  run    - Build and run the demo"
	@echo "  clean  - Remove build artifacts"
	@echo "  help   - Show this message"
