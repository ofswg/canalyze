CC = gcc
CFLAGS  = -Wall -std=c99

bin/main: build/main.o build/analyze.o build/process.o build/fileInfo.o bin
	$(CC) $(CFLAGS) -o bin/canalyze build/main.o build/fileInfo.o build/analyze.o build/process.o

build/main.o: src/main.c build
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

build/analyze.o: src/analyze.c build
	$(CC) $(CFLAGS) -c src/analyze.c -o build/analyze.o

build/fileInfo.o: src/fileInfo.c build
	$(CC) $(CFLAGS) -c src/fileInfo.c -o build/fileInfo.o

build/process.o: src/process.c build
	$(CC) $(CFLAGS) -c src/process.c -o build/process.o

.PHONY: clean

bin:
	mkdir bin

build:
	mkdir build

clean:
	rm -rf build bin
