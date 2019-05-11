bin/main:

bin/main: bin
	gcc -std=c99 -o bin/main src/main.c

bin:
	mkdir bin
