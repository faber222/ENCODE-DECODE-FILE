CC = g++
OBJECTS = ./libs/libbmp.cpp main.cpp function.cpp function.h 
LIBS = -I/usr/local/include/opencv4
CFLAGS = -Wall -Wextra -O2 
BINDIR = output
NAME = main
OUTPUT = $(BINDIR)/$(NAME)

checkerboard: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJECTS) $(LIBS) 
	

clean:
	rm -f $(OUTPUT)

run:
	./$(OUTPUT)
