CC := clang++
CFLAGS := -Wall -Wextra -Iinclude -g

SRC_DIR := ./src
BUILD_DIR := build
BIN := ./bin/parallax

# find all .c files under src/
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

# convert src/foo/bar.c -> build/foo/bar.o
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# default target
all: $(BIN)

# link object files into final binary
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# compile each .c into a .o in build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# clean up build and binary
clean:
	rm -rf $(BUILD_DIR) $(BIN)

.PHONY: all clean

