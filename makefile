CC := gcc
FLAGS := -Wall -Wextra -std=c11 -lSDL2 -lm
BIN_NAME := tetris
BUILD := build
SOURCE := src
OBJECT_FILES := $(BUILD)/main.o $(BUILD)/utils.o $(BUILD)/assets.o $(BUILD)/table.o $(BUILD)/parse.o $(BUILD)/list.o $(BUILD)/input.o $(BUILD)/event.o $(BUILD)/game.o

all: $(OBJECT_FILES)
	$(CC) $(BUILD)/*.o -o $(BUILD)/$(BIN_NAME) $(FLAGS)

# $^ points to the prerequisite and $@ to the target
$(BUILD)/%.o: $(SOURCE)/%.c
	$(CC) -c $^ -o $@

run: $(BUILD)/tetris
	./$(BUILD)/tetris	

clean:
	rm -rf $(BUILD)/*
