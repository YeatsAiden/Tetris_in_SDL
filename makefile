CC := gcc
FLAGS := -Wall -std=c99 -lSDL2
BIN_NAME := tetris
BUILD := build
SOURCE := src

all: $(BUILD)/main.o $(BUILD)/utils.o $(BUILD)/assets.o
	$(CC) $(BUILD)/*.o -o $(BUILD)/$(BIN_NAME) $(FLAGS)

# $^ points to the prerequisite and $@ to the target
$(BUILD)/%.o: $(SOURCE)/%.c
	$(CC) -c $^ -o $@

run: $(BUILD)/tetris
	./$(BUILD)/tetris	

clean:
	rm -rf $(BUILD)/*
