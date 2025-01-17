CC = gcc
CFLAGS = -Wall -Wextra
TARGET = hello

all: $(TARGET)

$(TARGET): main.c
 $(CC) $(CFLAGS) main.c -o $(TARGET)

clean:
 rm -f $(TARGET) *.o