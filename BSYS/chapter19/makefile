#
# Makefile disables compiler optimization
#
#
CC = gcc -o
CFLAGS = -g -W -Wall -std=$(STD) -pedantic -O0
STD = c11

TARGET = tlb

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TARGET).o

tlb: tlb.c
	$(CC) tlb tlb.c $(CFLAGS)

