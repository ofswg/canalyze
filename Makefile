bin/main:

bin/main: bin
	gcc -std=c99 -o bin/main src/main.c src/fileInfo.c src/analyze.c

bin:
	mkdir bin
