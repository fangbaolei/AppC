TARGET = hello
#cross compile
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
#flags
CFLAGS = -Wall
#object
OBJECTS += hello.o
OBJECTS += world.o 
#make
$(TARGET):$(OBJECTS)
	@$(CC) -o hello $(OBJECT) $(CFLAGS)
#clean
clean:
	@rm -f hello 
