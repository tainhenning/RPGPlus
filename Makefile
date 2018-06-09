#OBJS specifies which files to compile as part of the project 
OBJS = main.cpp main.h load.cpp load.h loadTexture.h loadTexture.cpp ltimer.h ltimer.cpp tile.cpp tile.h player.h player.cpp collision.h collision.cpp window.h window.cpp 
#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
#  COMPILER_FLAGS = -w
#
#  #LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -I /usr/include/SDL2/ -lSDL2 -lGL -lSDL2_image -w

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = 01_hello_SDL

#This is the target that compiles our executable
all : $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
