PROJECT_NAME=pz1
BIN_NAME=main

all: build

build: src/*
	mkdir -p build && cmake -S src -B build && make -C build

build_win: src/*
	rm -rf ./build && mkdir -p build &&\
	x86_64-w64-mingw32-cmake -S src -B build && make -C build

clean:
	make -C build clean

.SILENT: run
run: build
	echo; echo; echo "---------------$(PROJECT_NAME)---------------"; ./build/$(BIN_NAME)

.SILENT: run_win
run_win: build_win
	echo; echo; echo "---------------$(PROJECT_NAME)---------------"; ./build/$(BIN_NAME).exe

.PHONY: all build clean run build_win