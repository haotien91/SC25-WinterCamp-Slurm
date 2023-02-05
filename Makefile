# CC = $(MPICC)
CFLAGS += -std=c11

BUILD ?= build

SRC = $(wildcard src/*.c)
BIN = $(patsubst src/%.c,$(BUILD)/%,$(SRC))

all: $(BIN)

$(BUILD)/%: src/%.c | $(BUILD)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

clean:
	-rm -rf build/*
