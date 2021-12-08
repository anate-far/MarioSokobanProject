CC = gcc 
EXEC = bin/prog
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
CFLAGS = -W -Wall $(shell sdl2-config --cflags)
LDFLAGS = -export-dynamic $(shell sdl2-config --libs)
CC_SDL2_IMAGE = -lSDL2_image

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(CC_SDL2) $(CFLAGS) $(LDFLAGS) $(CC_SDL2_IMAGE) 

%.o : %.c
	$(CC) -c $(SRC) $(CFLAGS) $(LDFLAGS)

clean : 
	rm -rf *.o

mrproper : clean
	rm -rf $(EXEC)
