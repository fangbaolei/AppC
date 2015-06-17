#object
TARGET = main
OBJECT=main.o sum.o
#cross compile
CROSS_COMPILE = 
CC = $(CROSS_COMPILE)gcc
#flags
CFLAGS = -Wall -g
#install directory
INSTALL_DIR = Install

$(TARGET):$(OBJECT)
	$(CC) -o main $(OBJECT) $(CFLAGS)
main.o:sum.h

.PHONY:clean
clean:
	rm main *.o
