CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lraylib -lm -lX11

# Tell make that 'run' and 'clean' aren't actual files to avoid collisions
.PHONY: main run clean

main: main.c
	$(CC) main.c -o main $(CFLAGS) $(LIBS)

run: main
	./main

clean:
	rm -f main
