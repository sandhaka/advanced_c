CC=gcc
CFLAGS=-Wall -Wextra -pedantic
all: main
main: main.o other.o
	$(CC) $(CFLAGS) -o main main.o other.o
main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c
other.o: src/other.c
	$(CC) $(CFLAGS) -c src/other.c
clean: 
	rm -f main *.o