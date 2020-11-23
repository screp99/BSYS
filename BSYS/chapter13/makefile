CC= gcc -o
CFLAGS = -g -W -Wall -std=$(STD) -pedantic
STD= gnu17

TARGET = memory-user


EXECUTABLES = memory-user

.PHONY: all clean

all: $(TARGET)

clean:
	-rm -f $(EXECUTABLES) *.o

memory-user: memory-user.c
	$(CC) memory-user memory-user.c $(CFLAGS)

