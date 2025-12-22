CC = gcc
CFLAGS = -Wall -Iinclude

chess: src/main.c
	$(CC) $(CFLAGS) src/main.c -o chess

clean:
	rm -f chess