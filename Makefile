all: test.c opcodes.c
	mkdir -p build && gcc -o build/test test.c opcodes.c -I .
