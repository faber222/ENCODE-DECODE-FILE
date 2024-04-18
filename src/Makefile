CC = gcc
OBJECTS = ../libs/libbmp.c main.c function.c function.h
LIBS =
CFLAGS = -Wall -Wextra -O2
BINDIR = output
NAME = main
OUTPUT = $(BINDIR)/$(NAME)

checkerboard: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJECTS) $(LIBS) 2>/dev/null

clean:
	rm -f $(OUTPUT)

run:
	./$(OUTPUT)
