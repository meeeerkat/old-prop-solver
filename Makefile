CC = g++
LD = g++

# -O0 option to activate optimisations
CFLAGS = -Wall -Wextra -O0
LDFLAGS =

SRC_FILES := $(shell find src -regextype sed -regex ".*\.cpp" -type f)
OBJ_FILES=$(patsubst src/%.cpp,obj/%.o,$(SRC_FILES))
TARGET=bin/main

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(LD) $(OBJ_FILES) $(LDFLAGS) -o $@

obj/%.o: src/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJ_FILES)
