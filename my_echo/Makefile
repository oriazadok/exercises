CC ?= gcc
CFLAGS ?= -Wall

TARGET = my_echo

all: $(TARGET)

$(TARGET): my_echo.c
	$(CC) $(CFLAGS) -o $(TARGET) my_echo.c

clean:
	rm -f $(TARGET)

.PHONY: all clean
