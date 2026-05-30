CC      = gcc
CFLAGS  = -Wall -Wextra -g -Iinclude

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(filter-out $(SRC_DIR)/test.cpp,$(wildcard $(SRC_DIR)/*.cpp))
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

TARGET = $(BIN_DIR)/main
TEST_TARGET = $(BIN_DIR)/test
TEST_OBJS = $(OBJ_DIR)/test.o $(OBJ_DIR)/util.o $(OBJ_DIR)/trie.o

# ── Default target ────────────────────────────────────────────────
all: $(TARGET)
	./$(TARGET)

# ── Test target ────────────────────────────────────────────────────
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# ── Link ──────────────────────────────────────────────────────────
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_TARGET): $(TEST_OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

# ── Compile ───────────────────────────────────────────────────────
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# ── Auto-create output dirs ───────────────────────────────────────
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# ── Dependency includes ───────────────────────────────────────────
-include $(DEPS)

# ── Clean ─────────────────────────────────────────────────────────
.PHONY: all clean test
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)