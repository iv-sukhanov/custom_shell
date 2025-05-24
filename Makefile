.PHONY: build run clean

NAME = cshell
FILE ?= batch.txt
build:
	@mkdir -p build
	cd build && cmake .. && make

run: build
	./build/$(NAME)

run-batch: build
	./build/$(NAME) $(FILE)

clean:
	rm -rf build
