CC = gcc
CFLAGS += -Wall -Wextra
GENDIRS = bin lib test
LIBFLAGS = -fpic -shared
INCLUDES = include
LIBPATH = lib

.PHONY: all

all: allDirs lib test

allDirs:
	@mkdir -p $(GENDIRS)

lib: allDirs
	@$(CC) $(CFLAGS) $(LIBFLAGS) -I$(INCLUDES) src/linkedList.c -o $(LIBPATH)/linkedList.so

test: lib
	@$(CC) $(CFLAGS) $(LIBFLAGS) -I$(INCLUDES) src/testRunner.c -g -o lib/testRunner.so
	@$(CC) $(CFLAGS) -I$(INCLUDES) src/testLinkedList.c lib/linkedList.so lib/testRunner.so -o test/testLinkedList
	@test/testLinkedList