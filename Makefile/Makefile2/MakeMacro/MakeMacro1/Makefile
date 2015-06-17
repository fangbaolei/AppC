#target
TARGET = main
#object
OBJECT=main.o hello.o
#cross compile
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
#flags
CFLAGS = -Wall
#make
$(TARGET):$(OBJECT)
	$(CC) -o main $(OBJECT) $(CFLAGS)
main.o:hello.h
	$(CC) -c main.c $(CFLAGS)
hello.o:
	$(CC) -c hello.c $(CFLAGS)
.PHONY:clean
#clean
clean:
	rm -f main *.o 
