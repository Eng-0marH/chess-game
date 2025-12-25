CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I include

SRC = src/main.c src/board.c src/valid.c src/draw.c
OBJ = main.o board.o valid.o draw.o
TARGET = chess

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o main.o

board.o: src/board.c
	$(CC) $(CFLAGS) -c src/board.c -o board.o

valid.o: src/valid.c
	$(CC) $(CFLAGS) -c src/valid.c -o valid.o

draw.o: src/draw.c
	$(CC) $(CFLAGS) -c src/draw.c -o draw.o

clean:
	rm -f *.o $(TARGET)