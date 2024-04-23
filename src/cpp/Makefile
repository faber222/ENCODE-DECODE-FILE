CC = g++
OBJECTS = ./libs/libbmp.cpp main.cpp function.cpp function.h 
## isso carrega toda a lib opencv para o programa
LIBS = -I/usr/local/include/opencv4
CFLAGS = -Wall -Wextra -O2 
BINDIR = output
NAME = main
OUTPUT = $(BINDIR)/$(NAME)

checkerboard: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(OBJECTS) $(LIBS) --static 2>/dev/null

clean:
	rm -f $(OUTPUT)

run:
	./$(OUTPUT)
