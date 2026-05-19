CC = clang

RAYLIB_PATH = /usr/local

CFLAGS = -Wall -Wextra -gdwarf-4 \
	-isystem$(RAYLIB_PATH)/include

LDFLAGS = \
	-L$(RAYLIB_PATH)/lib -lraylib \
	-framework Cocoa \
	-framework IOKit \
	-framework CoreVideo \
	-framework OpenGL \
	-framework CoreFoundation \
	-framework CoreGraphics

SRC = ./src/*.c
OUT = ./build/main

build:
	mkdir -p build
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(OUT)

run: build
	./build/main

clean:
	rm -rf ./build/*
