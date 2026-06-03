CC      = gcc
CFLAGS  = -Wall -Wextra -g -Iinclude
GW_CC = x86_64-w64-mingw32-gcc

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(filter-out $(SRC_DIR)/test.cpp,$(wildcard $(SRC_DIR)/*.cpp))
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

GW_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%GW.o, $(SRCS))

TARGET = $(BIN_DIR)/main
TEST_TARGET = $(BIN_DIR)/test
TEST_OBJS = $(OBJ_DIR)/test.o $(OBJ_DIR)/util.o $(OBJ_DIR)/trie.o
GW_TARGET = $(BIN_DIR)/main.exe

# ── Default target ────────────────────────────────────────────────
all: $(TARGET)
# 	./$(TARGET)

# ── Test target ───────────────────────────────────────────────────
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# ── Cross-Compile for Windows (MinGW) ─────────────────────────────

windows: $(GW_TARGET)
	     cp ascii.txt $(BIN_DIR)

# ── Link ──────────────────────────────────────────────────────────
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_TARGET): $(TEST_OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(GW_TARGET): $(GW_OBJS) | $(BIN_DIR)
	$(GW_CC) $(CFLAGS) $^ -o $@

# ── Compile ───────────────────────────────────────────────────────
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(OBJ_DIR)/%GW.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(GW_CC) $(CFLAGS) -MMD -MP -c $< -o $@

# ── Auto-create output dirs ───────────────────────────────────────
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# ── Dependency includes ───────────────────────────────────────────
-include $(DEPS)

.PHONY: clean test

# ── Clean ─────────────────────────────────────────────────────────
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)