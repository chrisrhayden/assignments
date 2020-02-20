CC=g++
CFLAGS=-Wall -ggdb3 -std=c++98 -pedantic

VALGRIND_FLAGS=--leak-check=full --show-leak-kinds=all
VALGRIND_FLAGS+=--track-origins=yes --verbose --log-file=valgrind-out.txt

build:
	$(CC) $(CFLAGS) -o out/target_build src/*.cpp

run: build
	./out/target_build

val: build
	valgrind $(VALGRIND_FLAGS) ./out/target_build
