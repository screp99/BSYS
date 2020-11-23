CC= gcc -o
CFLAGS = -g -W -Wall -std=$(STD) -pedantic
STD= gnu17

TARGET = \
		measurement_sys_call \
		measurement_context_switch

EXECUTABLES = \
		sys_call \
		context_switch

.PHONY: all clean

all: $(TARGET)

clean:
	-rm -f $(EXECUTABLES) *.o

measurement_sys_call: measurement_sys_call.c
	$(CC) sys_call measurement_sys_call.c $(CFLAGS)

measurement_context_switch: measurement_context_switch.c
	$(CC) context_switch measurement_context_switch.c $(CFLAGS)