CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lraylib -lm -lX11

main: main.c
	$(CC) main.c -o main $(CFLAGS) $(LIBS)

run: main
	./main

clean:
	rm -f main
