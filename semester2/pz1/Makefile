PROJECT_NAME=pz1
BIN_NAME=main

all: build

build: src/*
	mkdir -p build && cmake -S src -B build  && make -C build

clean:
	make -C build clean

.SILENT: run
run: build
	echo; echo; echo "---------------$(PROJECT_NAME)---------------"; ./build/$(BIN_NAME)

.PHONY: all build clean run