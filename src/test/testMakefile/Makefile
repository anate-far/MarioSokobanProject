CC = gcc 
EXEC = bin/prog
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
CC_SDL2 = `sdl2-config --cflags --libs) -lSDL2_image`

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) -o $(EXEC) $(OBJ)

$(OBJ) : $(SRC)
	$(CC) -c $(SRC)

clean : 
	rm -rf *.o

mrproper : clean
	rm -rf $(EXEC)
