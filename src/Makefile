CC = gcc
OBJECTS = libbmp.c main.c
LIBS =
CFLAGS = -Wall -Wextra -O2
BINDIR = $(DESTDIR)/usr/bin
NAME = main

checkerboard: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBS) 2>/dev/null

clean:
	rm $(NAME)

run:
	./$(NAME)