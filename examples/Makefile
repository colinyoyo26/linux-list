CC = gcc
CFLAGS = -g -I../include -I../private -o

all:
	$(CC) $(CFLAGS) insert insert-sort.c
	$(CC) $(CFLAGS) quick quick-sort.c
	$(CC) $(CFLAGS) merge merge-sort.c

.PHONY: clean
clean:
	-rm insert quick merge *.png *.txt
