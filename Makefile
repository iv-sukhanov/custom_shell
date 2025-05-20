.PHONY: build run clean

build:
	@mkdir -p build
	cd build && cmake .. && make

run: build
	./build/cshell

clean:
	rm -rf build
