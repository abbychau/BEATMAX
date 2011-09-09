# Makefile for BEATMAX
# For Mac OS X (using homebrew)

include Makefile.common

CC = ccache g++-4.2
CFLAGS = -O3 -Wall -Werror -pedantic -g `sdl-config --cflags` -g
OUTPUT_NAME = Beatmax
LIBS = -framework OpenGL -framework OpenAL -L/usr/X11R6/lib  `sdl-config --libs` -lSDL_ttf -lSDL_image -lvorbisfile -lavcodec -lavformat -lavutil

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(OUTPUT_NAME) 

%.o : src/%.cpp 
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm -rf $(OBJ)
	rm -rf $(OUTPUT_NAME)

