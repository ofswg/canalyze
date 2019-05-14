bin/main:

bin/main: bin
	gcc -std=c99 -o bin/canalyze src/main.c src/fileInfo.c src/process.c

bin:
	mkdir bin
