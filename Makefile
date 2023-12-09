
CC=gcc
INCLUDE=include
LIBS=m
CFLAGS=-Wall -Wextra -mavx -g
DEFINES=DEBUG
EXENAME=raytr

SRC=$(wildcard src/*.c)
OBJS=$(SRC:src/%.c=build/%.o)

default: $(OBJS) makedirs
	mkdir -p build
	$(CC) $(OBJS) $(LIBS:%=-l%) -o build/$(EXENAME)

run: default
	./build/$(EXENAME)

build/%.o: src/%.c makedirs
	$(CC) $(CFLAGS) $(DEFINES:%=-D%) $(INCLUDE:%=-I%) -c $< -o $@

makedirs:
	mkdir -p build

.PHONY:
	clean

clean:
	rm -rf obj build
