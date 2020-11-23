CC= gcc -o
CFLAGS = -g -W -Wall -std=$(STD) -pedantic
STD= gnu17

TARGET = null malloc array arrayWithFree


EXECUTABLES = null malloc array arrayWithFree

.PHONY: all clean

all: $(TARGET)

clean:
	-rm -f $(EXECUTABLES) *.o

null: null.c
	$(CC) null null.c $(CFLAGS)

malloc: malloc.c
	$(CC) malloc malloc.c $(CFLAGS)

array: array.c
	$(CC) array array.c $(CFLAGS)

arrayWithFree: arrayWithFree.c
	$(CC) arrayWithFree arrayWithFree.c $(CFLAGS)
