.PHONY: build run clean

EXECUTABLE_NAME ?= ishell
BATCH_FILE ?= batch.txt

build:
	@mkdir -p build
	cd build && cmake -DEXECUTABLE_NAME=$(EXECUTABLE_NAME) .. && make

run: build
	./build/$(EXECUTABLE_NAME)

run-batch: build
	./build/$(EXECUTABLE_NAME) $(BATCH_FILE)

clean:
	rm -rf build
