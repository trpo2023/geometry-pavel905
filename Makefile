CC = gcc
CFLAGS = -Wall -Werror  #  Обновленные флаги
TARGET = geometry

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) main.c -o $(TARGET)

clean:
	rm -f $(TARGET) *.o